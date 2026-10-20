import React, { useState, useEffect, useRef } from "react";
import * as THREE from "three";
import { Node3D, Pipe3D, BcfAnnotation, Language } from "./types";

const mockNodes: Node3D[] = [
  { id: "SRC", x: -10, y: 0, z: 0, pressurePsi: 65.0, flowGpm: 250.0 },
  { id: "SPK-1", x: -5, y: 3, z: 0, pressurePsi: 45.2, flowGpm: 37.6, kFactor: 5.6 },
  { id: "SPK-2", x: 0, y: 3, z: 0, pressurePsi: 38.5, flowGpm: 34.7, kFactor: 5.6 },
  { id: "SPK-3", x: 5, y: 3, z: 0, pressurePsi: 32.1, flowGpm: 31.7, kFactor: 5.6 },
  { id: "SPK-4", x: 10, y: 3, z: 0, pressurePsi: 28.0, flowGpm: 29.6, kFactor: 5.6 }
];

const mockPipes: Pipe3D[] = [
  { id: "P-MAIN", startNodeId: "SRC", endNodeId: "SPK-1", diameterInches: 3.0, flowGpm: 250.0, frictionLossPsi: 2.1 },
  { id: "P-12", startNodeId: "SPK-1", endNodeId: "SPK-2", diameterInches: 2.0, flowGpm: 150.0, frictionLossPsi: 1.8 },
  { id: "P-23", startNodeId: "SPK-2", endNodeId: "SPK-3", diameterInches: 1.5, flowGpm: 90.0, frictionLossPsi: 1.5 },
  { id: "P-34", startNodeId: "SPK-3", endNodeId: "SPK-4", diameterInches: 1.25, flowGpm: 30.0, frictionLossPsi: 1.2 }
];

export const App: React.FC = () => {
  const [lang, setLang] = useState<Language>("fa");
  const [annotations, setAnnotations] = useState<BcfAnnotation[]>([
    {
      id: "bcf-1",
      elementId: "SPK-4",
      author: "Senior Fire Engineer",
      comment: "Check pressure margin per NFPA 13 Section 10.2",
      timestamp: new Date().toISOString().split("T")[0],
      position: [10, 3, 0]
    }
  ]);
  const [selectedElement, setSelectedElement] = useState<string | null>("SPK-1");
  const [newComment, setNewComment] = useState<string>("");

  const mountRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    if (!mountRef.current) return;

    const width = mountRef.current.clientWidth;
    const height = mountRef.current.clientHeight;

    const scene = new THREE.Scene();
    scene.background = new THREE.Color(0x0f172a);

    const camera = new THREE.PerspectiveCamera(60, width / height, 0.1, 1000);
    camera.position.set(0, 8, 25);

    const renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(width, height);
    mountRef.current.appendChild(renderer.domElement);

    const ambientLight = new THREE.AmbientLight(0xffffff, 0.7);
    scene.add(ambientLight);

    const dirLight = new THREE.DirectionalLight(0xffffff, 0.8);
    dirLight.position.set(10, 20, 15);
    scene.add(dirLight);

    // Grid floor
    const grid = new THREE.GridHelper(40, 20, 0x334155, 0x1e293b);
    grid.position.y = -2;
    scene.add(grid);

    // Draw Nodes (Sprinklers / Sources)
    mockNodes.forEach((node) => {
      const isSprinkler = node.kFactor !== undefined;
      const geometry = isSprinkler
        ? new THREE.ConeGeometry(0.6, 1.2, 16)
        : new THREE.SphereGeometry(1.0, 16, 16);

      // Color coding based on pressure heatmap
      let color = 0x22c55e; // Green
      if (node.pressurePsi < 30) color = 0xef4444; // Red (low pressure)
      else if (node.pressurePsi < 40) color = 0xeab308; // Yellow

      const material = new THREE.MeshStandardMaterial({ color, roughness: 0.3 });
      const mesh = new THREE.Mesh(geometry, material);
      mesh.position.set(node.x, node.y, node.z);
      if (isSprinkler) mesh.rotation.x = Math.PI; // Cone pointing down
      scene.add(mesh);
    });

    // Draw Pipes
    mockPipes.forEach((pipe) => {
      const n1 = mockNodes.find((n) => n.id === pipe.startNodeId);
      const n2 = mockNodes.find((n) => n.id === pipe.endNodeId);
      if (!n1 || !n2) return;

      const p1 = new THREE.Vector3(n1.x, n1.y, n1.z);
      const p2 = new THREE.Vector3(n2.x, n2.y, n2.z);
      const distance = p1.distanceTo(p2);

      const geometry = new THREE.CylinderGeometry(
        pipe.diameterInches * 0.1,
        pipe.diameterInches * 0.1,
        distance,
        16
      );
      const material = new THREE.MeshStandardMaterial({ color: 0x38bdf8, metalness: 0.6, roughness: 0.2 });
      const cylinder = new THREE.Mesh(geometry, material);

      const midPoint = new THREE.Vector3().addVectors(p1, p2).multiplyScalar(0.5);
      cylinder.position.copy(midPoint);
      cylinder.quaternion.setFromUnitVectors(new THREE.Vector3(0, 1, 0), p2.clone().sub(p1).normalize());

      scene.add(cylinder);
    });

    let animationFrameId: number;
    const animate = () => {
      animationFrameId = requestAnimationFrame(animate);
      scene.rotation.y += 0.002;
      renderer.render(scene, camera);
    };
    animate();

    return () => {
      cancelAnimationFrame(animationFrameId);
      if (mountRef.current) mountRef.current.innerHTML = "";
    };
  }, []);

  const handleAddAnnotation = () => {
    if (!newComment.trim() || !selectedElement) return;
    const selNode = mockNodes.find((n) => n.id === selectedElement);
    const pos: [number, number, number] = selNode ? [selNode.x, selNode.y, selNode.z] : [0, 0, 0];

    const newAnno: BcfAnnotation = {
      id: `bcf-${Date.now()}`,
      elementId: selectedElement,
      author: "Fire Design Engineer",
      comment: newComment,
      timestamp: new Date().toISOString().split("T")[0],
      position: pos
    };

    setAnnotations([...annotations, newAnno]);
    setNewComment("");
  };

  const isRtl = lang === "fa";

  return (
    <div
      style={{
        display: "flex",
        height: "100vh",
        width: "100vw",
        direction: isRtl ? "rtl" : "ltr",
        backgroundColor: "#0f172a",
        color: "#f8fafc"
      }}
    >
      {/* 3D WebGL Viewport */}
      <div style={{ flex: 1, position: "relative" }} ref={mountRef}>
        <div
          style={{
            position: "absolute",
            top: 16,
            left: isRtl ? "auto" : 16,
            right: isRtl ? 16 : "auto",
            zIndex: 10,
            background: "rgba(15, 23, 42, 0.85)",
            padding: "12px 20px",
            borderRadius: "8px",
            backdropFilter: "blur(8px)",
            border: "1px solid #334155"
          }}
        >
          <h2 style={{ margin: 0, fontSize: "18px", color: "#38bdf8" }}>
            {lang === "fa"
              ? "پلتفرم طراحی و شبیه‌سازی اطفای حریق"
              : "Fire Protection Design & Simulation Platform"}
          </h2>
          <p style={{ margin: "4px 0 0 0", fontSize: "12px", color: "#94a3b8" }}>
            {lang === "fa"
              ? "مدلسازی سه‌بعدی شبکه اسپرینکلر + نقشه حرارتی فشار (NFPA 13)"
              : "3D Sprinkler Network Viewer + Pressure Heatmap (NFPA 13)"}
          </p>
        </div>

        {/* Language Toggle */}
        <button
          onClick={() => setLang(lang === "en" ? "fa" : "en")}
          style={{
            position: "absolute",
            bottom: 20,
            left: isRtl ? "auto" : 20,
            right: isRtl ? 20 : "auto",
            zIndex: 10,
            background: "#0284c7",
            color: "#ffffff",
            border: "none",
            padding: "10px 18px",
            borderRadius: "6px",
            cursor: "pointer",
            fontWeight: "bold"
          }}
        >
          {lang === "en" ? "فارسی (Persian)" : "English"}
        </button>
      </div>

      {/* Side Panel: Calculation & BCF Pinning */}
      <div
        style={{
          width: "360px",
          background: "#1e293b",
          borderLeft: isRtl ? "none" : "1px solid #334155",
          borderRight: isRtl ? "1px solid #334155" : "none",
          padding: "20px",
          display: "flex",
          flexDirection: "column",
          gap: "20px",
          overflowY: "auto"
        }}
      >
        <div>
          <h3 style={{ margin: "0 0 12px 0", borderBottom: "1px solid #334155", paddingBottom: "8px" }}>
            {lang === "fa" ? "خلاصه محاسبات هیدرولیک" : "Hydraulic Calculation Summary"}
          </h3>
          <div style={{ fontSize: "14px", display: "grid", gap: "8px" }}>
            <div style={{ display: "flex", justifyContent: "space-between" }}>
              <span style={{ color: "#94a3b8" }}>{lang === "fa" ? "دبی کل سیستم:" : "Total Flow:"}</span>
              <strong style={{ color: "#38bdf8" }}>250 GPM (946 L/min)</strong>
            </div>
            <div style={{ display: "flex", justifyContent: "space-between" }}>
              <span style={{ color: "#94a3b8" }}>{lang === "fa" ? "فشار نقطه تقاضا:" : "Demand Pressure:"}</span>
              <strong style={{ color: "#38bdf8" }}>65.0 PSI (4.48 Bar)</strong>
            </div>
            <div style={{ display: "flex", justifyContent: "space-between" }}>
              <span style={{ color: "#94a3b8" }}>{lang === "fa" ? "استاندارد مرجع:" : "Reference Standard:"}</span>
              <span style={{ color: "#22c55e" }}>NFPA 13 (2022)</span>
            </div>
          </div>
        </div>

        {/* BCF Annotations Section */}
        <div>
          <h3 style={{ margin: "0 0 12px 0", borderBottom: "1px solid #334155", paddingBottom: "8px" }}>
            {lang === "fa" ? "یادداشت‌ها و نشانه‌گذاری BCF" : "BCF 3D Annotations"}
          </h3>

          <div style={{ display: "flex", flexDirection: "column", gap: "8px", marginBottom: "16px" }}>
            {annotations.map((a) => (
              <div
                key={a.id}
                style={{
                  background: "#0f172a",
                  padding: "12px",
                  borderRadius: "6px",
                  border: "1px solid #334155",
                  fontSize: "13px"
                }}
              >
                <div style={{ display: "flex", justifyContent: "space-between", color: "#38bdf8", fontWeight: "bold" }}>
                  <span>{a.elementId}</span>
                  <span style={{ fontSize: "11px", color: "#64748b" }}>{a.timestamp}</span>
                </div>
                <div style={{ margin: "4px 0", color: "#e2e8f0" }}>{a.comment}</div>
                <div style={{ fontSize: "11px", color: "#94a3b8" }}>
                  {lang === "fa" ? "ثبت توسط:" : "By:"} {a.author}
                </div>
              </div>
            ))}
          </div>

          <div style={{ display: "flex", flexDirection: "column", gap: "8px" }}>
            <label style={{ fontSize: "12px", color: "#94a3b8" }}>
              {lang === "fa" ? "انتخاب المان سه‌بعدی:" : "Select 3D Element:"}
            </label>
            <select
              value={selectedElement || ""}
              onChange={(e) => setSelectedElement(e.target.value)}
              style={{
                background: "#0f172a",
                color: "#f8fafc",
                border: "1px solid #334155",
                padding: "8px",
                borderRadius: "4px"
              }}
            >
              {mockNodes.map((n) => (
                <option key={n.id} value={n.id}>
                  {n.id} ({n.pressurePsi} PSI)
                </option>
              ))}
            </select>

            <textarea
              placeholder={
                lang === "fa"
                  ? "متن یادداشت مهندسی یا عدم انطباق را وارد کنید..."
                  : "Enter engineering or compliance comment..."
              }
              value={newComment}
              onChange={(e) => setNewComment(e.target.value)}
              rows={3}
              style={{
                background: "#0f172a",
                color: "#f8fafc",
                border: "1px solid #334155",
                padding: "8px",
                borderRadius: "4px",
                resize: "none"
              }}
            />

            <button
              onClick={handleAddAnnotation}
              style={{
                background: "#16a34a",
                color: "#ffffff",
                border: "none",
                padding: "10px",
                borderRadius: "4px",
                fontWeight: "bold",
                cursor: "pointer"
              }}
            >
              {lang === "fa" ? "ثبت نشانه‌گذاری BCF" : "Pin BCF Annotation"}
            </button>
          </div>
        </div>
      </div>
    </div>
  );
};
