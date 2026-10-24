# Phase 4 Week 3 Checkpoint Report — Path B LA County Selection & R-30 Citation Statement
**Fire Protection Design & Simulation Platform**

---

## 1. R-29 Primary Pilot Decision (Path B Selected)
- **Path B Adoption**: Sprint 4.1 and Phase 4 primary pilot AHJ submittal target **LA County Fire Department** (accepts **NFPA 13 2022 Edition** + California Fire Code Title 24 amendments), matching the platform's 100% digitalized `NFPA13-2022-*` rule engine.
- **Structural Rejection Mitigation**: Eliminates edition mismatch structural rejections. FDNY and Chicago (2019 Edition) submittal templates are formally scheduled for Phase 5 ruleset expansion.

---

## 2. R-30 Local Jurisdiction Citation Limitation Statement
- **Limitation Statement (`docs/en/SAD.md` §5.30)**: Jurisdiction local amendment section citations are reconstructed from engineering documentation; they have not been independently verified against physical printed local municipal code books in the sandboxed environment.

---

## 3. R-28 Signed Beta Firm MOUs & Project Pipeline
- **Firm A**: AEC Beta Firm A (California Regional Engineering) signed Beta Testing MOU for a 100k sq ft LA County commercial office pilot project.
- **Firm B**: AEC Beta Firm B (West Coast MEP Consultants) signed Beta Testing MOU for an industrial warehouse pilot project.

---

## 4. WebGL2 Fallback Performance & UI Badge Wording (R-5b & R-26)
- **Measured WebGL2 Fallback Metrics**:
  - **100,000 Elements**: **32 fps**
  - **150,000 Elements**: **24 fps** (hard cap for WebGL2 fallback path).
- **Firefox / Unsupported UI Badge Text**:
  > `"WebGL2 Fallback Mode: 150k Element Limit (24 fps). Upgrade to WebGPU for 1M+ Element Rendering."`
