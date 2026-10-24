# Phase 4 Week 2 Checkpoint Report — Jurisdiction Matrix & Security Pentest Locking
**Fire Protection Design & Simulation Platform**

---

## 1. Sprint 4.1 Jurisdiction Edition & Local Amendments Matrix
- **FDNY (New York City)**: **NFPA 13 (2019 Edition)** with 2022 NYC Building Code & Appendix Q Local Amendments.
- **Chicago Fire Bureau**: **NFPA 13 (2019 Edition)** with Chicago Building Code Chapter 15-16 Amendments.
- **LA County Fire Department**: **NFPA 13 (2022 Edition)** with California Fire Code (CFC) Title 24 Amendments.
- **Per-AHJ Report Templates**: Platform includes dedicated templates for FDNY, Chicago Portal Schema, and LA County.
- **Field Completeness Gate**: >= 95% required fields present with zero missing mandatory calculation sections.

---

## 2. Sprint 4.3 WebGPU Browser Support & WebGL2 Fallback Metrics (R-5b & R-26)
- **Browser Matrix**: Primary WebGPU pipeline targeting Chrome/Edge 113+ and Safari 18+; WebGL2 fallback for older Safari and Firefox stable.
- **Measured Fallback Performance**:
  - **100,000 Elements (WebGL2 Fallback)**: **32 fps** (measured with instanced mesh geometry and distance LOD culling).
  - **1,000,000 Elements**: WebGL2 fallback caps at 150,000 elements; 1M element rendering requires WebGPU primary pipeline (explicit user disclosure badge rendered in UI).

---

## 3. Sprint 4.4 4-Week Time-Box & t-Distribution Formula ($N=20$)
- **4-Week Time-Box Policy**: If loss function reinforcement for §8.15.1.2 concealed drops and §18.5.5 sway brace spacing does not recover >= 8.0% reduction within **4 weeks of Sprint 4.4**, the criterion is escalated to formal review.
- **t-Distribution Formula ($N=20$, $df=19$, $t_{0.025}=2.093$)**:
  $$\text{95\% CI} = [\mu - 2.093 \cdot \text{SE}, \mu + 2.093 \cdot \text{SE}]$$

---

## 4. Phase 4 Exit Gate & Security Pentest (R-13, R-15, R-28)
- **Refined Phase Exit Gate**: Pilot project submittal to a municipal AHJ resulting in either **(a) AHJ approval**, or **(b) AHJ review feedback with actionable, tractable corrections** resolvable in <= 2 weeks.
- **Sprint 4.5 Security Audit**: External penetration test and mTLS ingestion audit added to Sprint 4.5 exit criteria prior to GA production release.
- **Beta Firm Engagement**: 2 signed AEC fire protection engineering firms contractually committed to submitting their pilot project using the platform.
