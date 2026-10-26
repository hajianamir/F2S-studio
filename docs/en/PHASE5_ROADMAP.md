# Phase 5 Development Roadmap & Multi-Edition Architecture Strategy
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 5 Kickoff Scope & Decoupled Execution Strategy
Phase 5 engineering executes in parallel with the external Phase 4 LA County Municipal AHJ review track. The Phase 4 Feb 15, 2027 submittal package remains frozen and decoupled from Phase 5 code changes.

### Five Core Kickoff Items & Resolution
1. **Multi-Edition Rule Engine Architecture**:
   - The rule engine treats edition releases as discrete, versioned JSON files (`core/rules/nfpa13_2019.json` alongside `core/rules/nfpa13_2022.json`).
   - Rule sets are loaded independently into the `RuleEngine` instance, ensuring zero side-effects between standards.
2. **2019 vs. 2022 NFPA 13 Delta Analysis**:
   - *Chapter Reorganization*: NFPA 13 (2019) Chapter 8 (Sprinkler Installation) was reorganized into Chapter 10 in NFPA 13 (2022).
   - *Concealed Space Protection*: §8.15.1.2 (2019) vs §10.2.8.1 (2022) section numbering deltas mapped cleanly in JSON rule definitions.
   - *Coexistence Verification*: Evaluates dual-edition evaluation side-by-side on a single network model with zero calculation engine modifications.
3. **Sprint 5.2 High-Piled Storage Scope**:
   - Minimal pilot-support set (25 rules) covering Commodity Classes I–IV, racking configurations, and ESFR density curves specifically tuned for Firm B warehouse pilot.
4. **Sprint 5.3 IoT Security & Telemetry Pipeline Execution**:
   - Executes in parallel with Sprint 5.1/5.2. Features mTLS 1.3 authentication, RBAC, 10 Hz rate limiting, 90-day hot / 3-year cold retention, and automated anomaly detection.
5. **Phase 4 Freeze Confirmation**:
   - Phase 4 LA County package remains 100% frozen. Feb 15, 2027 formal submittal track operates on dedicated release tag `v1.0.0-phase4-frozen`.

---

## 2. Phase 5 Sprint Sequence & Exit Criteria

- **Sprint 5.1**: NFPA 13 (2019 Edition) Rule Set & Dual-Edition Coexistence Test.
- **Sprint 5.2**: High-Piled Storage Occupancy Rules (Chapters 12–20, Commodity Classes I–IV).
- **Sprint 5.3**: Production IoT Telemetry Pipeline (mTLS, RBAC, Rate Limiting, TimescaleDB).
- **Sprint 5.4**: FDNY Local Submittal Template (2019 Building Code).
- **Sprint 5.5**: Chicago Fire Code Submittal Template (2019 Title 14B).
- **Sprint 5.6**: Firm B Warehouse Pilot Project Submittal Package.
- **Sprint 5.7**: GA Commercial Positioning & Multi-Edition Regulatory Sign-Off.
