# Phase 4 Roadmap, Exit Criteria & Customer Validation Strategy (v7)
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 4 Phase-Level Exit Definition & Pilot Designation
- **Primary Exit Pilot Designation (Firm A)**:
  - **Firm A (California Regional Engineering)**: 100k sq ft Light Hazard (LH) commercial office building in LA County. **Designated as Sole Phase 4 Exit Gate Primary Pilot Project**. Target submittal date: **Q1 2027 (Week 12 of Phase 4)**.
  - **R-33 Pre-Submittal Consultation**: Scheduled for **Week 8 of Phase 4** with LA County Fire Department. Agenda: report format, Title 24 amendments, digital PE stamp schema, BCF annotation index.
- **Secondary Stretch Pilot (Firm B)**:
  - **Firm B (West Coast MEP Consultants)**: Industrial Warehouse (Storage Occupancy S-1/S-2). Formally classified as a **Phase 5 Stretch Validation Test**.
- **Phase Exit Criteria**:
  1. **Primary Pilot AHJ Submittal**: Active pilot submittal to LA County Fire Department resulting in **(a) AHJ approval**, or **(b) AHJ feedback with actionable, tractable corrections** resolvable in <= 2 weeks.
  2. **Designer Usability Score (Path B R-36 Selected)**: **SUS score >= 75** across $N = 10$ PEs ($N=8$ external PEs reported separately from $N=2$ beta firm PEs).
  3. **Verified Viewport Performance**: 1,000,000 element 3D WebGPU viewport rendering at **>= 30 fps**.

---

## 2. Sprint 4.1 Result: LA County Report Quality Verification (R-15 PASS)
- **Primary Target Jurisdiction**: **LA County Fire Department** (NFPA 13 2022 Edition + California Fire Code Title 24 Amendments).
- **Submittal Package Layout**: **PE-Corrected Final Layout** ($3,901.7\text{ ft}$).
- **Sample Report Artifact**: Generated `benchmark/reports/lacounty_submittal_report_sample.json`.
- **Field Completeness Result**: **100.0% Required Fields Present** (zero missing mandatory calculation sections), comfortably passing the $\ge 95\%$ gate. **Sprint 4.1 Passed**.

---

## 3. R-37 Phase 5 Formal Commitment & Kickoff Schedule
- **Phase 5 Formally Authorized & Committed**: Kickoff scheduled for **Q2 2027**.
- **Phase 5 Scope**:
  1. **FDNY & Chicago Rule Sets**: NFPA 13 (2019 Edition) + 2022 NYC Appendix Q and Chicago Title 15 local amendments.
  2. **Storage Occupancies**: NFPA 13 Chapters 12–20 high-piled pallet storage rulesets (enabling Firm B warehouse GA submittal).
