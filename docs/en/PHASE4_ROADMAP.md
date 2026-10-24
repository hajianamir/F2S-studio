# Phase 4 Roadmap, Exit Criteria & Customer Validation Strategy (v4)
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 4 Phase-Level Exit Definition & R-29 Edition Decision
- **R-29 Edition Decision (Path B Selected)**:
  - Primary Phase 4 Pilot Project & AHJ Submittal is targeted exclusively at **LA County Fire Department** (accepts **NFPA 13 2022 Edition** + California Title 24 Amendments), matching the platform's 100% digitalized `NFPA13-2022-*` rule engine.
  - **FDNY** and **Chicago Fire Bureau** (2019 Edition) submittal templates are formally scheduled for Sprint 4.1b / Phase 5 ruleset expansion.
- **Phase Exit Criteria**:
  1. **Pilot Project AHJ Submittal**: At least **1 active pilot project** submitted to LA County Fire Department plan review using the platform-generated report package, resulting in **(a) AHJ approval**, or **(b) AHJ review feedback with actionable, tractable corrections** resolvable in <= 2 weeks. Structural rejections (edition/format) do not count as success.
  2. **Designer Usability Score**: **SUS score >= 75** across $N >= 5$ practicing PE design engineers.
  3. **Verified Viewport Performance**: 1,000,000 element 3D WebGPU viewport rendering at **>= 30 fps** (WebGL2 fallback at 100k: 32 fps, 150k: 24 fps).

---

## 2. Sprint 4.1: LA County Fire Department Report Quality & Verification (R-15, R-25, R-29)
- **Primary Target Jurisdiction**: **LA County Fire Department** (NFPA 13 2022 Edition + California Fire Code Title 24 Amendments).
- **Submittal Package Layout**: **PE-Corrected Final Layout** (Post-remediation model, $3,901.7\text{ ft}$).
- **Required Fields Checklist**: Project metadata, PE stamp signature block & audit trail (R-12 schema), code edition tag (`NFPA13-2022`), hydraulic calculation summary, K-factor orifice schedule, pipe velocity/pressure loss tables, and BCF 3D annotation index.
- **Pass Threshold**: **>= 95% required fields present** with zero missing mandatory calculation sections.

---

## 3. Sprint 4.2: Designer-in-the-Loop Usability Testing (R-16 & R-28)
- **R-28 Signed Beta Firm MOUs**:
  1. **AEC Beta Firm A** (California Regional Engineering): Signed Beta Testing MOU for 100k sq ft LA County commercial office pilot project.
  2. **AEC Beta Firm B** (West Coast MEP Consultants): Signed Beta Testing MOU for industrial warehouse pilot project.
- **Critical Task Matrix**: Project creation, IFC4 import, hydraulic run, clash review, seismic bracing calculation, AHJ report generation, digital PE stamp.
- **Pass Threshold**: **System Usability Scale (SUS) >= 75** across 5 PEs; **>= 85% completion rate**.

---

## 4. Sprint 4.3: WebGPU Performance & Fallback Badge Wording (R-5b, R-26)
- **Browser Matrix (2026)**: Primary WebGPU pipeline targeting Chrome/Edge 113+ and Safari 18+; WebGL2 fallback for older Safari and Firefox stable.
- **Measured WebGL2 Fallback Metrics**:
  - **100,000 Elements**: **32 fps**
  - **150,000 Elements**: **24 fps** (hard cap for WebGL2 fallback path).
- **UI Badge Text (Firefox / Unsupported WebGPU)**:
  > `"WebGL2 Fallback Mode: 150k Element Limit (24 fps). Upgrade to WebGPU for 1M+ Element Rendering."`

---

## 5. Sprint 4.4: AI Constraint Reinforcement & 4-Week Time-Box (R-20)
- **4-Week Time-Box Policy**: If loss function reinforcement for §8.15.1.2 concealed drops and §18.5.5 sway brace spacing does not recover >= 8.0% reduction within **4 weeks of Sprint 4.4**, the criterion is escalated to formal review.
- **t-Distribution Statistical Formula ($N=20$, $df=19$, $t_{0.025}=2.093$)**:
  $$\text{95\% CI} = [\mu - 2.093 \cdot \text{SE}, \mu + 2.093 \cdot \text{SE}]$$

---

## 6. Sprint 4.5: IoT Digital Twin Pipeline & Security Pentest (R-13 & R-27)
- **Security Audit Requirement**: External penetration test and mTLS ingestion audit completed prior to GA production release.
