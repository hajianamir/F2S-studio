# Phase 6 Development Roadmap & Technical Scope (Option 3)
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 6 Detailed Sprint Scoping & Exit Criteria (Option 3)

### Sprint 6.1 — General High-Piled Storage Expansion
- **Objective**: Extend storage rules from Class III (Sprint 5.2 baseline) to Group A/B/C plastics, roll paper, and rubber tire storage.
- **Scope**: Group A/B/C plastics density curves, roll paper storage, rubber tire storage. Estimated 35–45 rules.
- **Measurable Exit Criteria**: Rule count enumerated with coverage matrix; non-compliant discriminator tests PASS for each storage class; reference calcs vs PE hand calc <1% deviation; AI optimizer constraint set includes all new rules.
- **Effort & Risk**: 6–7 weeks effort. High complexity on Group A plastic density curves.

### Sprint 6.2 — In-Rack Sprinkler Matrix Calculations (NFPA 13 Ch 25)
- **Objective**: Implement in-rack sprinkler hydraulic calculations for racked storage configurations.
- **Scope**: Single/double/multi-row rack parsing, in-rack head placement rules, combined ceiling + in-rack matrix hydraulic solver extension.
- **Measurable Exit Criteria**: 25 in-rack rules enumerated; racked warehouse reference calculation vs PE hand calc <1% deviation; non-compliant rack discriminator test PASS; AI optimizer updated.
- **Effort & Risk**: 4–6 weeks effort. High risk on hydraulic solver matrix extension.

### Sprint 6.3 — Stage 2 Enterprise Cloud Infrastructure
- **Objective**: Migrate from Stage 1 (single-AZ EC2 + RDS) to Stage 2 (EKS multi-AZ, per-tenant KMS, CloudHSM, 7-year WORM).
- **Event-Driven Trigger (R-99 Resolved)**: Activated upon reaching **10 active commercial firm tenants OR $300,000 ARR, whichever comes first**.
- **Measurable Exit Criteria**: EKS multi-AZ failover tested (<5 min RTO); per-tenant KMS isolation verified; CloudHSM cluster operational; 7-year WORM verified.
- **Effort & Risk**: 8–12 weeks effort. High infrastructure cost ($1,500–$3,000/mo) if triggered prematurely.

### Sprint 6.4 — WebGPU Full-Model 30+ FPS Optimization
- **Objective**: Raise full-model-view performance from 22.4 FPS to 30+ FPS at 1,000,000 mixed MEP primitives in full overview camera mode.
- **Scope**: LOD geometry hierarchy, GPU-side compute shader culling, instanced mesh optimization.
- **Measurable Exit Criteria**: **30+ FPS achieved** at 1,000,000 mixed primitives in full-model overview camera mode (culling minimal); 34.5 FPS typical view maintained.
- **Effort & Risk**: 3–4 weeks effort. Medium optimization plateau risk.

### Sprint 6.5 — Multi-Constraint AI Layout Optimization
- **Objective**: Extend AI optimizer from single-objective (footage) to multi-constraint (footage + brace count + clash avoidance + code compliance).
- **Scope**: Multi-objective Pareto frontier reporting, expanded Phase 6 rule constraint integration (Option 2 requirement).
- **Measurable Exit Criteria**: Pareto frontier of >=5 valid solutions across 3 objectives; each solution passes 100% of implemented rules; AI optimizer constraint set covers 100% of Phase 6 rules.
- **Effort & Risk**: 4–6 weeks effort. Medium risk on multi-objective trade-off degradation.

### Sprint 6.6 — Enterprise SSO Integration
- **Objective**: Implement SAML 2.0 and OIDC enterprise identity integration.
- **Scope**: SAML 2.0 (Okta, Azure AD), OIDC (Auth0), SCIM 2.0 user provisioning, group-to-role mapping.
- **Measurable Exit Criteria**: SAML/OIDC authentication verified against Okta and Azure AD test tenants; SCIM user provisioning lifecycle verified; setup guide published.
- **Effort & Risk**: 5 weeks effort. Low risk.

---

## 2. Phase 6 Execution Sequencing & Phase 6 Exit Gate

### Execution Sequencing
```
Weeks 1–7:   Sprint 6.1 (Storage Expansion)  [parallel with Sprint 6.6]
Weeks 1–5:   Sprint 6.6 (Enterprise SSO)     [independent]
Weeks 6–12:  Sprint 6.2 (In-Rack Solver)     [depends on 6.1]
Weeks 8–13:  Sprint 6.4 (WebGPU 30+ FPS)    [parallel]
Weeks 13–19: Sprint 6.5 (Multi-AI Extensions) [depends on 6.1 & 6.2]
Event-Driven: Sprint 6.3 (Stage 2 Cloud)     [Trigger: 10 tenants OR $300k ARR]
```

### Phase 6 Exit Gate Definition
> **Phase 6 Exit Gate**: Phase 6 officially exits when:
> 1. Sprints 6.1, 6.2, 6.5, and 6.6 are complete with all measurable exit criteria satisfied.
> 2. Sprint 6.4 is complete (30+ FPS at 1M full-model overview) or formally deferred to Phase 7 with documented plateau analysis.
> 3. Sprint 6.3 is complete OR un-triggered (if commercial tenant/revenue threshold is not yet met).
> 4. AI optimizer constraint set covers 100% of active rule engine rules (Option 2 finding enforced).
> 5. Bilingual documentation is complete across all closed Phase 6 sprints.
