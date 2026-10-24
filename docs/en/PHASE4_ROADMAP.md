# Phase 4 Roadmap, Exit Criteria & Customer Validation Strategy (v3)
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 4 Phase-Level Exit Definition
- **Phase Exit Criteria (Refined)**:
  1. **Pilot Project AHJ Submittal**: At least **1 active pilot project** submitted to a municipal AHJ plan review using the platform-generated report package, resulting in either **(a) AHJ approval**, or **(b) AHJ review feedback with actionable, tractable corrections** resolvable in <= 2 weeks. Structural rejections (edition mismatch / unusable format) do not count as success.
  2. **Designer Usability Score**: **SUS score >= 75** across $N >= 5$ practicing PE design engineers.
  3. **Verified Viewport Performance**: 1,000,000 element 3D WebGPU viewport rendering at **>= 30 fps** (with WebGL2 fallback at 100k elements).

---

## 2. Sprint 4.1: AHJ Report Quality & Jurisdiction Verification (R-15 & R-25)
- **Layout Model Tested**: **PE-Corrected Final Layout** (Post-remediation model, $3,901.7\text{ ft}$).
- **Jurisdiction Editions & Local Amendments Matrix**:
  1. **FDNY** (NYC Fire Department): **NFPA 13 (2019 Edition)** with 2022 NYC Building Code & Appendix Q Local Amendments.
  2. **Chicago Fire Bureau**: **NFPA 13 (2019 Edition)** with Chicago Building Code Chapter 15-16 Amendments.
  3. **LA County Fire Department**: **NFPA 13 (2022 Edition)** with California Fire Code (CFC) Title 24 Amendments.
- **Template Scope**: Dedicated **Per-Jurisdiction Submittal Templates** (FDNY Template, Chicago Portal Schema Template, LA County Template).
- **Pass Threshold**: **>= 95% required fields present** with zero missing mandatory calculation sections.

---

## 3. Sprint 4.2: Designer-in-the-Loop Usability Testing (R-16)
- **Recruit Profile**: 5 licensed Professional Engineers (PE) / Senior Fire Protection Designers (2 signed beta firms) with >= 5 years experience.
- **Critical Task Matrix**: Project creation, IFC4 import, hydraulic run, clash review, seismic bracing calculation, AHJ report generation, digital PE stamp.
- **Pass Threshold**: **System Usability Scale (SUS) >= 75**; **>= 85% completion rate**.

---

## 4. Sprint 4.3: WebGPU Performance, Browser Support & Fallback (R-5b & R-26)
- **Browser Matrix (2026)**:
  - **WebGPU Primary**: Chrome 113+, Edge 113+, Safari 18+.
  - **WebGL2 Fallback**: Older Safari (<18), Firefox stable.
- **Measured Fallback Performance**:
  - **100,000 elements (WebGL2 Fallback)**: **32 fps** (measured locally with distance LOD culling and non-blocking compatibility badge).
  - **1,000,000 elements**: Capped at 150,000 elements under WebGL2 fallback; 1M elements requires WebGPU primary pipeline (explicit user disclosure badge).

---

## 5. Sprint 4.4: AI Constraint Reinforcement & Statistical CI (R-20)
- **Time-Box Policy**: If optimizer improvements do not recover $\ge 8.0\%$ reduction within **4 weeks of Sprint 4.4**, the criterion is escalated to formal review.
- **t-Distribution Statistical Formula ($N=20$, $df=19$, $t_{0.025}=2.093$)**:
  $$\text{95\% CI} = [\mu - 2.093 \cdot \text{SE}, \mu + 2.093 \cdot \text{SE}]$$

---

## 6. Sprint 4.5: IoT Digital Twin Pipeline & Security Pentest (R-13 & R-27)
- **Deployment**: Hybrid SaaS / Self-Hosted Docker Container.
- **Security Audit Requirement**: External penetration test and mTLS ingestion audit completed prior to GA production release.

---

## 7. R-28 Beta Firm Agreements
- **Beta Firm Commitments**: 2 regional AEC fire protection engineering firms under signed non-disclosure agreements, contractually committed to submitting their pilot project using the platform.
