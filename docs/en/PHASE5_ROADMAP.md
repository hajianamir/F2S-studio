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
