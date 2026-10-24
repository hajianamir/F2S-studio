# Phase 4 Roadmap, Exit Criteria & Customer Validation Strategy
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 4 Phase-Level Exit Definition
- **Phase Exit Criteria (Option A)**:
  1. **Pilot Project AHJ Submittal**: At least **1 active pilot project** submitted to a real Municipal AHJ plan review using the platform-generated PE-stamped report package (`report.pdf`).
  2. **Designer Usability Score**: **SUS score >= 75** across $N >= 5$ practicing PE design engineers.
  3. **Verified Performance**: 1,000,000 element 3D WebGL/WebGPU viewport rendering at **>= 30 fps**.

---

## 2. Sprint 4.1: AHJ Report Quality Validation (R-15)
- **Layout Model Tested**: **PE-Corrected Final Layout** (Post-remediation model from Sprint 3.2, pipe footage = $3,901.7\text{ ft}$).
- **Target Jurisdictions**:
  1. **FDNY** (New York City Fire Department Plan Examination)
  2. **Chicago Fire Prevention Bureau**
  3. **LA County Fire Department**
- **Required Fields Checklist**: Project info, PE stamp signature block (R-12 audit schema), code edition tag (`NFPA13-2022`), hydraulic calculation summary, K-factor orifice schedule, pipe velocity/pressure loss tables, and BCF 3D annotation index.
- **Pass Threshold**: **>= 95% required fields present** with zero missing mandatory calculation sections; verified PE stamp signature workflow logged.

---

## 3. Sprint 4.2: Designer-in-the-Loop Usability Testing (R-16)
- **Recruit Profile**: 5 licensed Professional Engineers (PE) / Senior Fire Protection Designers with >= 5 years AutoCAD/Revit experience.
- **Critical Task Matrix**:
  1. Create project & import IFC4 model.
  2. Execute hydraulic network calculation & review pressure heatmap.
  3. Run MEP spatial clash detection & resolve hard clash.
  4. Run NFPA 13 Ch 18 seismic sway bracing calculation.
  5. Generate AHJ report & apply digital PE stamp.
- **Pass Threshold**: **System Usability Scale (SUS) >= 75**; **>= 85% completion rate** on critical task matrix.

---

## 4. Sprint 4.3: WebGPU 1M Element Viewport Performance & Fallback (R-5b & R-26)
- **Target Renderer**: WebGPU / Instanced Compute Buffers.
- **R-26 Browser Fallback Architecture**:
  - **Primary**: WebGPU pipeline (Chrome 113+, Edge 113+).
  - **Fallback**: Auto-detects unsupported browsers (Safari, Firefox, legacy Chrome) and seamlessly falls back to **Three.js Instanced Mesh WebGL2 Rendering** with distance LOD culling, maintaining 30+ fps at 100k elements and displaying a non-blocking browser compatibility badge.

---

## 5. Sprint 4.4: AI Constraint Reinforcement & Pre-Measurement Decision (R-20 & R-28)
- **Loss Function Reinforcement**: Soft penalty loss added for §8.15.1.2 concealed drops and §18.5.5 sway brace spacing violations during loss gradient evaluation.
- **Pre-Measurement Decision (R-20)**: If loss function reinforcement drops footage reduction below $8.0\%$, the **optimizer architecture will be improved** (reinforcing branch line routing heuristics) to meet the $\ge 8.0\%$ target; the $8.0\%$ target will **not** be revised down.
- **Stochastic Trial Matrix**: $N = 20$ trials evaluated; reported as $95\%$ Confidence Interval ($[\mu - 1.96 \cdot \text{SE}, \mu + 1.96 \cdot \text{SE}]$).

---

## 6. Sprint 4.5: IoT Digital Twin Read-Only Telemetry Pipeline (R-13 & R-27)
- **Deployment Architecture (R-27)**: Offered as **Hybrid SaaS / Self-Hosted Docker Edge Container** to support air-gapped fire safety networks.
- **SLA & Latency**: Telemetry ingestion throughput >= 1,000 msg/sec; dashboard stream latency < 200 ms; AES-256 encrypted time-series storage.

---

## 7. R-28 Customer Validation & Demand Pipeline
- **Active Demand Pipeline**: 2 regional AEC fire protection engineering firms engaged under signed non-disclosure / beta testing agreements for Sprint 4.1 submittal validation and Sprint 4.2 usability testing.
