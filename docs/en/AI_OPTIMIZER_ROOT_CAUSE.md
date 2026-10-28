# AI Optimizer Root-Cause Analysis & Rule-Set Feedback Policy (Option 2)
**Fire Protection Design & Simulation Platform**

---

## 1. Symptom & Historical Performance Restatement
- **Phase 3 Baseline (N=5 Trials)**: AI optimizer achieved 8.55% raw pre-correction pipe footage reduction. However, PE review identified 100% violation rates for concealed drop (§8.15.1.2) and sway brace clearance (§18.5.5). Post-correction footage yielded 8.20% (with 1 trial at 7.86% failing the 8.0% floor).
- **Phase 4 Baseline (N=20 Trials)**: Applied constraint reinforcement, achieving 8.16% ± 0.24% mean reduction (95% CI [8.05%, 8.27%]). Zero violations occurred on the acceptance run. Net savings dropped by only 0.04 percentage points.

---

## 2. Evaluation of Five Hypotheses
1. **H1 — 2D Abstraction Blindness**: False. The optimizer operates on a 3D graph representation.
2. **H2 — Rule-Set Incompleteness (PRIMARY ROOT CAUSE)**: **Confirmed**. §8.15.1.2 and §18.5.5 were explicitly out of scope during Phase 3 rule engine development. The optimizer faithfully optimized layouts against an incomplete rule set; post-hoc PE review caught violations of rules the optimizer was never instructed to enforce. Constraint reinforcement in Phase 4 added these 2 rules to the constraint set, eliminating violations with minimal (0.04pp) footage cost.
3. **H3 — Soft-Constraint Penalty Trading**: Partially true. In Phase 3, unconstrained rules acted as zero-penalty soft constraints.
4. **H4 — Training Distribution Gap**: False. Optimization heuristics operate deterministically on graph topology rather than machine-learning dataset shortcuts.
5. **H5 — Objective Function Misalignment**: Confirmed mechanism. Footage cost vs vertical drop cost was unweighted in the Phase 3 objective function.

---

## 3. Mandatory Phase 6 AI Rule-Set Feedback Loop Policy
- **Mandatory Policy**: Every future rule engine expansion sprint (e.g. Sprints 6.1 & 6.2) must feed newly implemented rule constraints directly into the AI optimizer constraint set before declaring AI compliance.
- **Rule Coverage Check**: CI pipeline enforces 100% mapping between active rule engine JSON files and AI optimizer loss-function penalty terms.
