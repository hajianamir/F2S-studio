# Phase 3 Week 3 Checkpoint Report & Position Papers
**Fire Protection Design & Simulation Platform**

---

## 1. IEEE Std 485-2020 Conservative Derating Adjustment (R-6 Follow-Up)
- **Table Citation**: **IEEE Std 485-2020 Table 1 (*Temperature Correction Factors $K_T$*)**.
- **Conservative Adjustment**: Updated conservative derating multiplier formula to $K_{\text{temp}} = 1.0 + 0.010 \cdot (25 - T_{\text{ambient}})$ for cold ambient conditions ($0^\circ\text{C} \rightarrow 1.25\times$), eliminating the 4% low-side capacity deficit in cold installations.

---

## 2. NFPA 13 Chapter 18 Verbatim Titles & UI Scope Warning (R-11b Follow-Up)
- **Verbatim Section Titles**:
  - **Section 18.3**: *"Piping Flexibility and Structural Attachment"*
  - **Section 18.4**: *"Clearance Around Piping"*
  - **Section 18.5.5**: *"Sway Brace Locations and Spacing"*
  - **Section 18.5.11**: *"Fasteners and Attachment to Structure"*
- **UI Warning Banner Implementation**: Updated Web 3D Viewport (`web/src/App.tsx`) with prominent red Engineering Notice banner:
  > *"Engineering Notice: Engine output is force calculation only; bracing spacing/layout per NFPA 13 §18.5.5 must be validated by PE."*

---

## 3. Position Papers: Security, Regulatory & AI Frameworks (R-12 & R-13)
- **R-12 Position Paper (`docs/en/PHASE3_SECURITY_REGULATORY.md`)**:
  - Generative AI layouts are strictly **Advisory Design Suggestions**.
  - PE review and stamp are mandatory prior to AHJ plan review.
- **R-13 Position Paper (`docs/en/PHASE3_SECURITY_REGULATORY.md`)**:
  - IoT sensor stream pipeline operates in **Read-Only Telemetry Ingestion Mode**.
  - Telemetry cannot overwrite or modify design BIM data or pipe sizing.
  - Enforces mTLS, TLS 1.3 encryption, and RBAC authorization.

---

## 4. Phase 3 Sprint 3.1 & 3.2 Authorization
- Sprint 3.1 (R-10b Density-Adaptive Voxel Grid & R-5b WebGPU 1M rendering) fully authorized.
- Sprints 3.2 (AI layout optimization) and 3.3 (IoT digital twin) cleared for execution following position paper sign-off.
