# Phase 2 Engineering Strategy & Roadmap
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 2 Sequenced Execution Strategy

Per the Phase 1 Sign-Off Addendum, Phase 2 execution follows a dependency-ordered sprint plan:

### Sprint 1 (Item 2E - Verification Infrastructure & Native AOT)
- **R-1 Closure**: Remote CI execution against target GitHub repository upon deployment, validating lcov coverage >= 80.0%.
- **R-3 Closure**: Native AOT publication pass for `.NET 8` API and native `P/Invoke` test suite execution against compiled AOT binary.

### Sprint 2 (Item 2C - Multi-Standard Rule Coexistence)
- **R-7 Closure**: Implementation of **EN 12845** (European Automatic Sprinkler Standard) and **BS 9251** (British Residential Sprinkler Standard) rulesets.
- Verification of side-by-side standard coexistence (`NFPA13-2022`, `EN12845-2020`, `BS9251-2021`) on single project instances without core engine modifications.

### Sprint 3 (Item 2D - H2X / HydraCALC Cross-Validation Automation)
- **R-2 & R-4 Closure**: Automated benchmark validation runner comparing C++ core outputs against published H2X and HydraCALC test cases, including real-world messy IFC exports.

### Sprint 4 (Item 2A - MEP Clash Detection)
- Pipe-vs-Duct and Pipe-vs-Structure spatial interference detection between fire protection piping and mechanical/structural elements.

### Sprint 5 (Item 2B - NFPA 13 Chapter 18 Seismic Bracing)
- Seismic zone design, sway brace sizing, and zone of influence calculations per NFPA 13 Chapter 18.
