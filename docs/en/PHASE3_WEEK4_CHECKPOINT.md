# Phase 3 Week 4 Checkpoint Report & Risk Register Updates
**Fire Protection Design & Simulation Platform**

---

## 1. R-6 Hot-Ambient Capping & IEEE 485 Table Verification
- **IEEE Std 485-2020 Table Citation**: Verified against **IEEE Std 485-2020 Table 1 (*Temperature Correction Factors $K_T$*)**. Applied conservative $0.010 / ^\circ\text{C}$ ($1.0\% / ^\circ\text{C}$) derating.
- **Hot-Ambient Capping Enforcement**: In `core/src/fire_alarm.cpp`, hot-ambient capacity credit is explicitly **capped at $K_{\text{temp}} = 1.00$** for $T_{\text{ambient}} > 25^\circ\text{C}$ ($77^\circ\text{F}$), preventing unsafe battery undersizing in elevated ambient mechanical rooms ($40^\circ\text{C}$).

---

## 2. R-11b NFPA 13 (2022) Verbatim Quotes & UI Warning Banner Verification
- **Verbatim Section Quotes**: Documented in `docs/en/SAD.md` §5.4 with exact page references for Section 18.3 (p. 13-182), Section 18.4 (p. 13-185), Section 18.5.5 (p. 13-189), and Section 18.5.11 (p. 13-195).
- **UI Engineering Notice Banner**: Rendered prominently in Web 3D Viewport (`web/src/App.tsx`):
  > *"Engineering Notice: Engine output is force calculation only; bracing spacing/layout per NFPA 13 §18.5.5 must be validated by PE."*

---

## 3. Position Papers & R-14 AI MVP Acceptance Criteria
- **R-12 Position Paper (`docs/en/PHASE3_SECURITY_REGULATORY.md`)**:
  - Detailed audit log JSON structure (model version, PE user ID, action, topology hash, modification reasons).
  - Liability disclaimer: AI outputs are advisory suggestions; PE assumes full professional responsibility.
  - AHJ submittal policy: Permit packages render **ONLY the final PE-stamped design**.
- **R-13 Threat Model (`docs/en/PHASE3_SECURITY_REGULATORY.md`)**:
  - Unidirectional read-only telemetry pipeline, data-at-rest AES-256 encryption, rate-limiting, and sensor spoofing anomaly alerts.
- **R-14 AI MVP Acceptance Criteria**:
  - **Single Objective**: Minimize total pipe run footage subject to 100% NFPA 13 compliance.
  - **Measurable Metric**: Achieve **$\ge 8.0\%$ reduction in total pipe footage** compared to standard manual grid layout on a 100k sq ft Light Hazard office model.

---

## 4. Phase 3 Roadmap Amendments & Spot-Audit Schedule
- **Sprint 3.4 (R-15)**: Added AHJ Report Quality Verification Sprint.
- **Sprint 3.5 (R-16)**: Added Designer-in-the-Loop Usability Testing Sprint with 5 active PEs.
- **Spot-Audit Schedule**: Sampled `THIRD_PARTY_NOTICES.md` CDDL disclosure and `benchmark/report.md` per-node deviation table (100% verified).
