# Third-Party Notices & License Compliance

This software includes third-party open-source libraries and components. Below is the list of third-party software packages used in this MVP release, along with their respective licensing terms:

---

## 1. xBIM Toolkit (xBIM.Ifc, xBIM.Common, xBIM.Ifc4, xBIM.Ifc2x3)
- **License**: CDDL 1.0 (Common Development and Distribution License)
- **Usage**: Used in `backend/src/Infrastructure/Ifc4BimAdapter.cs` for IFC4 building information model parsing, entity extraction, and structured object mapping.
- **Compliance Statement**:
  - The xBIM Toolkit binaries are consumed via official NuGet package references without any source code modification.
  - Per CDDL 1.0 requirements, xBIM remains separate as a dynamically linked dependency. No xBIM source code has been altered or directly embedded.

---

## 2. Three.js
- **License**: MIT License
- **Usage**: Used in `web/src/App.tsx` for 3D WebGL rendering of pipe networks, sprinkler heads, and pressure heatmap visual overlays.

---

## 3. Vazirmatn Font
- **License**: SIL Open Font License 1.1 (OFL-1.1)
- **Usage**: Used in `web/index.html` and `web/src/App.tsx` for Persian typography and RTL UI layout rendering.

---

## 4. xUnit & Microsoft.NET.Test.Sdk
- **License**: Apache License 2.0 / MIT License
- **Usage**: Used in `backend/tests/BackendTests` for automated unit and integration testing.

---

## 5. React & Vite
- **License**: MIT License
- **Usage**: Used in `web/` for frontend single-page application framework and build bundling.
