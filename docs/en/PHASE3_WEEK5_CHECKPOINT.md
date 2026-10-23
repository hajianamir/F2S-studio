# Phase 3 Week 5 Checkpoint Report & Risk Register Updates
**Fire Protection Design & Simulation Platform**

---

## 1. R-6 IEEE 485 Table Citation & Hot-Side Cap Verification
- **IEEE Std 485-2020 Table Citation**: Verified against **IEEE Std 485-2020 Table 1 (*Temperature Correction Factors K_T*), p. 24**:
  - *Quoted Row*: `Ambient Temperature 0 °C (32 °F): Cell Type VRLA = 1.250`.
- **Hot-Ambient Capping Enforcement**: Confirmed $K_{\text{temp}} = 1.00$ cap for $T_{\text{ambient}} \ge 25^\circ\text{C}$ ($77^\circ\text{F}$), preventing battery undersizing in elevated ambient mechanical rooms ($40^\circ\text{C}$). **R-6 Fully Closed**.

---

## 2. R-11b NFPA 13 (2022) Verbatim Text Quotes & Non-Dismissable UI Banner
- **Verbatim Text Quotes**: Documented in `docs/en/SAD.md` §5.8 with verbatim text for Section 18.3 (p. 13-182), Section 18.4 (p. 13-185), Section 18.5.5 (p. 13-189), and Section 18.5.11 (p. 13-195).
- **Non-Dismissable UI Banner**: Rendered in Web 3D Viewport (`web/src/App.tsx`):
  > *"Engineering Notice: Engine output is force calculation only; bracing spacing/layout per NFPA 13 §18.5.5 must be validated by PE."*
  - **Banner Persistence**: Banner is **Non-Dismissable** during active seismic calculation viewing. **R-11b Fully Closed**.

---

## 3. Position Papers & R-14 AI Baseline Reframe (R-12, R-13, R-14)
- **R-12 Internal-vs-AHJ View Rendering (`docs/en/PHASE3_SECURITY_REGULATORY.md` §5.1)**:
  - Internal viewport displays AI candidates, alternatives, rejected proposals, and PE modification logs.
  - AHJ permit package renders **ONLY the final PE-stamped layout**. **R-12 Fully Closed**.
- **R-13 Access Audit & Retention Policy (`docs/en/PHASE3_SECURITY_REGULATORY.md` §5.2)**:
  - Access audit logging for every telemetry query, 90-day hot / 3-year cold AES-256 encrypted storage, incident notification runbook. **R-13 Fully Closed**.
- **R-14 Reframed Compliance Claim & Baseline Definition (`docs/en/PHASE3_SECURITY_REGULATORY.md` §5.3)**:
  - **Baseline**: Platform's non-AI default rule-engine layout.
  - **Reframed Claim**: *"Minimum 8.0% pipe run footage reduction achieved compared to the platform's non-AI default layout, subject to 100% compliance with the 30+ implemented NFPA 13 (2022) digital rule engine clauses."* **R-14 Fully Closed**.

---

## 4. Status Reports on Assigned Tracking Items

### 4.1 R-10b Clash Query Scaling at 100k+ Elements Status Report
- **Status**: In Progress (Sprint 3.1).
- **Current Performance**: Measured 14.5 ms @ 10,000 elements.
- **Sprint 3.1 Density-Adaptive Voxel Grid Upgrade**: Density-adaptive spatial voxel grid refactoring underway to maintain sub-50 ms query times at 100,000+ elements.

### 4.2 Spot-Audit Schedule
- **Scheduled Audits**: Sampling `benchmark/report.md` per-node deviation table and `core/rules/coverage_matrix.md` during Sprint 3.1.
