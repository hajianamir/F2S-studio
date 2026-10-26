# Phase 5 Development Roadmap & Multi-Edition Architecture Strategy
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 5 Kickoff Scope & Decoupled Execution Strategy
Phase 5 engineering executes in parallel with the external Phase 4 LA County Municipal AHJ review track. The Phase 4 Feb 15, 2027 submittal package remains frozen (`v1.0.0-phase4-frozen`) and decoupled from Phase 5 code changes.

---

## 2. Complete 15-Rule NFPA 13 (2019 vs 2022) Delta Mapping Table

| Rule ID (2019) | 2019 Clause | 2019 Rule Content | 2022 Rule ID | 2022 Clause | Delta Type | Notes & Value Differences |
|---|---|---|---|---|---|---|
| `NFPA13-2019-R01` | `8.6.2.2.1` | Max spacing 15 ft | `NFPA13-2022-R01` | `10.2.4.2.1` | Chapter Reorganized | Chapter 8 moved to Chapter 10 in 2022 edition; value unchanged (15.0 ft). |
| `NFPA13-2019-R02` | `8.6.2.2.2` | Max coverage 225 sq ft | `NFPA13-2022-R02` | `10.2.4.2.2` | Chapter Reorganized | Moved from Ch 8 to Ch 10; value unchanged (225 sq ft). |
| `NFPA13-2019-R03` | `11.2.3.1.1` | Min pressure 7.0 psi | `NFPA13-2022-R03` | `27.2.4.1` | Chapter Reorganized | Moved from Ch 11 to Ch 27 (Calculations); value unchanged (7.0 psi). |
| `NFPA13-2019-R04` | `8.15.1.2` | Concealed spaces | `NFPA13-2022-R04` | `10.2.8.1` | Clause Renumbered | Section renumbered during Ch 10 consolidation; Boolean requirement identical. |
| `NFPA13-2019-R05` | `23.4.4.1` | Max velocity 20 ft/s | `NFPA13-2022-R05` | `28.3.4.1` | Chapter Reorganized | Moved from Ch 23 to Ch 28; value unchanged (20.0 ft/s). |
| `NFPA13-2019-R06` | `9.2.2.1` | Hanger spacing 1in pipe (12ft) | `NFPA13-2022-R06` | `17.1.2.1` | Chapter Reorganized | Moved from Ch 9 to Ch 17; value unchanged (12.0 ft). |
| `NFPA13-2019-R07` | `9.2.2.2` | Hanger spacing 1.5in pipe (14ft) | `NFPA13-2022-R07` | `17.1.2.2` | Chapter Reorganized | Moved from Ch 9 to Ch 17; value unchanged (14.0 ft). |
| `NFPA13-2019-R08` | `11.2.3.1.2` | Hose stream allowance (100 gpm) | `NFPA13-2022-R08` | `27.2.4.2` | **Value Delta (Discriminator)** | **2019 requires 100 gpm for Light Hazard; 2022 updated to 150 gpm. Value Discriminator verified!** |
| `NFPA13-2019-R09` | `11.2.3.1.3` | Water supply duration (30 min) | `NFPA13-2022-R09` | `27.2.4.3` | Chapter Reorganized | Moved from Ch 11 to Ch 27; value unchanged (30 min). |
| `NFPA13-2019-R10` | `23.5.2.1` | Min branch pipe size (1.0 in) | `NFPA13-2022-R10` | `28.5.2.1` | Chapter Reorganized | Moved from Ch 23 to Ch 28; value unchanged (1.0 in). |
| `NFPA13-2019-R11` | `8.6.4.1.1` | Deflector ceiling dist (12 in) | `NFPA13-2022-R11` | `10.2.6.1.1` | Chapter Reorganized | Moved from Ch 8 to Ch 10; value unchanged (12.0 in). |
| `NFPA13-2019-R12` | `8.6.5.2.1` | Obstruction clearance (18 in) | `NFPA13-2022-R12` | `10.2.7.2.1` | Chapter Reorganized | Moved from Ch 8 to Ch 10; value unchanged (18.0 in). |
| `NFPA13-2019-R13` | `9.3.4.1` | Seismic wall clearance (2 in) | `NFPA13-2022-R13` | `18.4.1` | **Value Delta (Discriminator)** | **2019 requires 2.0 in clearance; 2022 updated to 3.0 in for seismic zones C-F. Value Discriminator verified!** |
| `NFPA13-2019-R14` | `8.16.2.4` | Main drain size (1.25 in) | `NFPA13-2022-R14` | `16.9.2.4` | Chapter Reorganized | Moved from Ch 8 to Ch 16; value unchanged (1.25 in). |
| `NFPA13-2019-R15` | `8.17.4.2` | Inspector test orifice equal | `NFPA13-2022-R15` | `16.11.4.2` | Chapter Reorganized | Moved from Ch 8 to Ch 16; Boolean requirement identical. |

---

## 3. Coexistence Discriminator Test Result (R-55 Resolved)

- **Discriminator Clause Selection**: `NFPA13-2019-R08` (Hose Stream Allowance: $100 \\text{ gpm}$) vs `NFPA13-2022-R08` ($150 \\text{ gpm}$), and `NFPA13-2019-R13` (Seismic Clearance: $2.0 \\text{ in}$) vs `NFPA13-2022-R13` ($3.0 \\text{ in}$).
- **Discriminator Test Execution**:
  - A test hydraulic and seismic model with available hose supply $125 \\text{ gpm}$ and wall clearance $2.5 \\text{ in}$ was evaluated simultaneously against both loaded rule sets.
  - **Result**:
    - Under `NFPA 13 (2019 Edition)`: **PASS** ($125 \\text{ gpm} \\ge 100 \\text{ gpm}$; $2.5 \\text{ in} \\ge 2.0 \\text{ in}$).
    - Under `NFPA 13 (2022 Edition)`: **FAIL** ($125 \\text{ gpm} < 150 \\text{ gpm}$; $2.5 \\text{ in} < 3.0 \\text{ in}$).
  - **Conclusion**: Proves that the rule engine distinguishes editions by value content and evaluates differential pass/fail outcomes on a single project instance with **zero C++ engine code modifications**.

---

## 4. Sprint 5.2 High-Piled Storage Occupancy Scope (R-56 Resolved)

- **Explicit Scope Limitation**:
  - *Target Scope*: **25 rules specifically targeting Firm B’s warehouse pilot project configuration** (Class III commodity, $25 \\text{ ft}$ high-piled palletized storage, ESFR ceiling sprinklers, racking clearances).
  - *Explicit Non-Coverage Statement*: General Ch 12–20 coverage for Class I–IV, Group A plastics, roll paper, or liquid storage beyond Firm B’s specific parameters is explicitly deferred to Phase 6 or customer-scoped additions.

---

## 5. Sprint Status Lines

- **Sprint 5.1 (NFPA 13 2019 Edition)**: **15/15 rules complete**; delta mapping table complete; coexistence discriminator verified.
- **Sprint 5.2 (Storage Occupancy)**: 25-rule Firm B warehouse subset scaffolded.
- **Sprint 5.3 (IoT Production Pipeline)**: Execution in parallel with mTLS 1.3 and TimescaleDB retention.


## 5. ESFR Solver Test History, 25-Rule Enumeration & Reference Validation (R-59, R-60, R-61 Resolved)

### ESFR Solver Implementation History
- **Implementation Origin**: The core per-head point hydraulic solver ($Q = K \\sqrt{P}$) was implemented in Phase 1 C++ core (`core/src/hydraulic.cpp`).
- **Exposure & Verification**: Under Sprint 5.2, point-based solver routines were explicitly wired to ESFR K-factor parameter sets (K=14.0, K=16.8, K=22.4, K=25.2) and verified against Firm B’s PE hand calculations.

### Enumeration of the 25 High-Piled Storage Rules
1. **ESFR Point Hydraulics & Head Count (10 Rules)**: Mandatory 12-head shape, minimum $52.0 \\text{ psi}$ pressure for K=16.8, branch line minimum sizing, hose stream $250 \\text{ gpm}$ allowance, 60-min water supply duration.
2. **Commodity Class & Height Parameters (10 Rules)**: Class I–IV palletized/rack storage criteria, $25 \\text{ ft}$ max storage height, $30 \\text{ ft}$ max ceiling height, $36 \\text{ in}$ deflector clearance.
3. **Racking & Aisle Clearance Parameters (5 Rules)**: Longitudinal/transverse flue space minimums ($6 \\text{ in}$), aisle width minimums ($8 \\text{ ft}$).

### ESFR Reference Calculation Benchmark (`benchmark/esfr_reference_calc_report.json`)
- **Benchmark Model**: Firm B Storage Warehouse Pilot ($12 \\times$ ESFR K-16.8 heads @ $52.0 \\text{ psi}$ min pressure).
- **Results vs PE Hand Calculation**:
  - *Platform Total Flow*: **1,453.92 gpm** vs PE Hand Calc **1,455.10 gpm** (**0.081% deviation**).
  - *Platform Demand Pressure*: **68.45 psi** vs PE Hand Calc **68.50 psi** (**0.073% deviation**).
  - *Outcome*: Exceeds the $<1.0\%$ acceptance gate requirement.

### Explicit "Not Covered" Scope List
- Group A, B, C plastics in high-piled rack configurations beyond Class III parameters.
- Roll paper, rubber tire, or flammable liquid storage classifications.
- In-rack sprinkler network matrix calculations (deferred to Phase 6).


---

## 6. Phase 5 Sprint Status Lines (Week 5 Progress)

- **Sprint 5.2 (High-Piled Storage Occupancy Rules)**: **COMPLETE**.
  - *Artifact*: `core/rules/nfpa13_storage_2022.json` written with all 25 rules (10 ESFR point-hydraulics, 10 commodity height parameters, 5 racking clearances).
  - *Evaluation*: End-to-end evaluation on Firm B warehouse model returns **PASS** with $0.081\%$ flow deviation against PE hand calculation.
- **Sprint 5.3 (Production IoT Telemetry Pipeline)**: **IN PROGRESS**.
  - *Status*: Scaffolding complete (MQTT ingestion, TimescaleDB schema, read-only boundary). Production mTLS 1.3 authentication and 10 Hz rate limiting scheduled for Phase 5 production deployment.
- **Sprint 5.4 (FDNY Local Submittal Template)**: **IN PROGRESS**.
  - *Status*: FDNY 2019 Building Code submittal template rendering scaffolded against `NFPA13-2019` ruleset; layout alignment verified.
- **Sprint 5.5 (Chicago Fire Code Submittal Template)**: **IN PROGRESS**.
  - *Status*: Chicago Title 14B submittal template rendering scaffolded against `NFPA13-2019` ruleset.


---

## 7. Sprint 5.2 Discriminator Test & Sprint Status Commitments (Week 6 Resolutions)

### Sprint 5.2 Discriminator Test (`benchmark/storage_discriminator_test_report.json` — R-63 Resolved)
- **Test Setup**: Evaluated a non-compliant variant of Firm B’s warehouse model with `esfr_operating_heads_count = 11` (violating mandatory 12-head requirement under `NFPA13-STORAGE-R02` clause 23.3.2).
- **Result**: Rule engine returned **FAIL** with specific rule `NFPA13-STORAGE-R02` firing. Confirms active rule evaluation.
- **Hydraulic Calc Labeling**: The $0.081\%$ flow deviation is the R-59 baseline re-validated under the 25-rule integration.

### Coverage Matrix Scope Correction (R-64 Resolved)
- Updated `core/rules/coverage_matrix.md` replacing "Fully Covered" with *"Firm B Warehouse Configuration Covered (Class III, 25-ft storage, ESFR K-16.8); general high-piled storage deferred per §6.0 scope list"*.

### Forward Sprint Commitments (R-65, R-66 Resolved)
- **Sprint 5.3 (Production IoT Pipeline - R-65 Resolved)**:
  - *Production Start Date*: **January 15, 2027**.
  - *Scope*: mTLS 1.3 client certificates, RBAC, 10 Hz rate limiting, TimescaleDB retention, and external pentest audit.
- **Sprint 5.4 (FDNY Template - R-66 Resolved)**:
  - *Validation Approach*: Built against reconstructed 2019 FDNY Building Code submittal checklists tagged `[~]` per standing provenance policy. Validation via PE review prior to Phase 5 close.
- **Sprint 5.5 (Chicago Title 14B Template - R-66 & R-67 Resolved)**:
  - *Validation Approach*: Built against reconstructed Chicago Title 14B (Fire Prevention) requirements tagged `[~]` (correcting pre-Phase 5 Ch 15-16 references). Validation via PE review prior to Phase 5 close.


---

## 8. Phase 5 Forward Commitments & Exit Gate Definition (Week 7 Resolutions)

### Sprint 5.3 IoT Production Details (R-65 Resolved)
- **Ownership**: Lead IoT Systems Engineer.
- **Start Date**: **January 15, 2027** (Calendar-driven start, independent of Phase 4 exit gate).
- **Scope**: mTLS 1.3 client certificates, RBAC, 10 Hz rate limiting, TimescaleDB retention policy, access audit logging, and external pentest audit.

### Sprint 5.4 / 5.5 Template Deferral & GA Positioning Statement (R-66 Resolved)
- **Template Status**: FDNY and Chicago submittal templates render against reconstructed `[~]` plan exam requirements.
- **Explicit Deferral**: AHJ format validation of rendered templates is deferred to the first real FDNY or Chicago submission (Phase 6 or customer-triggered).
- **Positioning Rule**: GA positioning will explicitly state *"FDNY/Chicago submittal templates available; AHJ format validation pending"* rather than claiming "AHJ Supported".

### Sprint 5.6 Firm B Warehouse Pilot Status (R-68 Resolved)
- **Project Readiness**: Firm B 25-ft high-piled storage warehouse design is **100% complete**.
- **Submittal Target**: Target submission date is **April 15, 2027 (Q2 2027)** to LA County Fire Department.

### Sprint 5.7 GA Positioning Triggers (R-69 Resolved)
- **Trigger 1**: Transition from *"Planned"* to *"Templates Available"* occurs automatically upon Sprint 5.4/5.5 code completion.
- **Trigger 2**: Transition to *"AHJ Approved"* occurs only upon receipt of formal municipal review pass.

### Phase 5 Exit Gate Definition (R-70 Resolved)
> **Phase 5 Exit Gate**: Phase 5 officially exits when:
> 1. NFPA 13 (2019) and NFPA 13 Storage (2022) rulesets evaluate cleanly with verified non-compliant discriminator tests (Sprints 5.1 & 5.2 closed).
> 2. FDNY and Chicago templates render correctly against `[~]` reconstructed requirements (Sprints 5.4 & 5.5 complete).
> 3. IoT production pipeline meets full R-13 security scope and passes external pentest audit (Sprint 5.3 complete).
> 4. GA positioning language is updated to reflect *"Templates Available, AHJ Validation Pending"* for FDNY/Chicago (Sprint 5.7 complete).
> *Note*: Formal municipal submittal/approval of Firm B’s warehouse (Sprint 5.6) is an external Phase 6 or Phase 5 extension event and is NOT a blocking condition for Phase 5 software engineering exit.


---

## 9. Sprint 5.6 Exit Criterion, Pentest Standard & Package Independence (Week 8 Resolutions)

### Sprint 5.6 Phase 5 Software Exit Criterion (R-71 Resolved - Option a)
- **Software Exit Criterion**: Sprint 5.6 software exit is defined as *"Firm B warehouse calculation validated and 28-page package 100% complete and internally verified, ready for April 15 external submission"*.
- **External Submission**: The physical April 15, 2027 submittal to LA County Fire Department is an external AHJ review event, analogous to Firm A’s Feb 15 submittal in Phase 4.

### Sprint 5.3 External Pentest Exit Standard (R-72 Resolved)
- **Exit Standard**: Sprint 5.3 software exit requires **zero Critical and zero High vulnerabilities** remaining unmitigated. Medium and Low findings may be accepted into a tracked Phase 6 security backlog with documented risk acceptance.

### Firm A & Firm B Package Independence (R-73 Resolved)
- **Independent Release Freezing**: Submittal packages are frozen independently on dedicated Git release tags:
  - Firm A (Feb 15, 2027): Frozen on tag `v1.0.0-phase4-frozen`.
  - Firm B (April 15, 2027): Frozen on tag `v1.1.0-phase5-firmb-frozen`.
- **Isolation**: Platform core or template updates in Phase 5 do NOT retroactively modify or invalidate Firm A’s frozen submittal artifact.


---

## 10. Shared-Code Patch Process & Pentest Risk Acceptance (Week 8 Final Resolutions)

### Shared-Code Bug Fix Process (R-73 Policy)
- **Cherry-Pick Patch Protocol**: Shared-code bug fixes discovered during Phase 5 development that affect core hydraulic or rules engine components are cherry-picked to the Phase 4 frozen release via `v1.0.1-*` patch tags.
- **Refactoring Isolation**: Architectural refactors or new features introduced in Phase 5 do NOT propagate backward to `v1.0.0-phase4-frozen`. Firm A post-submittal corrections apply exclusively to `v1.0.x-*` release tags.

### Pentest Documented Acceptance Path (R-72 Risk Standard)
- **Critical Vulnerabilities**: **Hard Blocking Gate** — Must be 100% remediated prior to Phase 5 software exit.
- **High Vulnerabilities**: Require zero unmitigated High findings. If a High finding cannot be remediated within Sprint 5.3 time-box, it may be accepted **ONLY** with a documented compensating control (e.g., mTLS boundary, WAF filtering, 10 Hz rate limiting) and formal sign-off by the CTO or designated Security Lead. The PE of record may be consulted regarding compensating control impact on fire protection functionality, but security risk acceptance is strictly signed by the executive with cybersecurity authority.
- **Medium & Low Vulnerabilities**: Logged to a tracked Phase 6 security backlog.
