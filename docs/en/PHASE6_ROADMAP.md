# Phase 6 Development Roadmap & Technical Scope (Option B)
**Fire Protection Design & Simulation Platform**

---

## 1. Phase 6 Technical Objectives, Sprints & Exit Criteria (R-98 Resolved)

| Sprint | Technical Scope | Measurable Software Exit Criteria (R-98) |
|---|---|---|
| **Sprint 6.1** | General Storage Rules (Group A/B/C Plastics, Roll Paper, Tires) | 30 new rules in `nfpa13_storage_expanded.json`; non-compliant discriminator tests PASS for each storage class. |
| **Sprint 6.2** | In-Rack Sprinkler Matrix Calculations (NFPA 13 Ch 25) | C++ solver matrix extension verified against PE hand calculation baseline (<1.0% deviation). |
| **Sprint 6.3** | Stage 2 Enterprise Cloud Infrastructure (EKS, CloudHSM, WORM) | Automated EKS failover test (<5 min RTO), CloudHSM seal signing verified, WORM 7-year lock verified. |
| **Sprint 6.4** | WebGPU Full-Model View Optimization | **30+ FPS** achieved at 1,000,000 mixed primitives in full-model overview camera view (culling minimal). |
| **Sprint 6.5** | Multi-Constraint AI Layout Extensions | Multi-standard (NFPA/EN/BS) AI optimization achieving >=8.0% footage reduction across 20 trials. |
| **Sprint 6.6** | Enterprise SSO Integration | SAML 2.0 / OIDC authentication verified with Azure AD and Okta test tenants. |

---

## 2. Stage 2 Infrastructure Trigger & Sequencing (R-99, R-100 Resolved)

### Stage 2 Infrastructure Activation Trigger (R-99 Resolved)
- Stage 2 EKS Multi-AZ, CloudHSM, and WORM storage activation is **event-driven** (not date-driven).
- **Trigger Condition**: Activated when total active commercial firm tenants exceed **10 firms** OR annual recurring revenue (ARR) clears **$300,000**.

### Phase 6 Execution Sequencing (R-100 Resolved)
- **Phase A**: Sprints 6.1 + 6.2 in parallel (Storage rules expansion & In-Rack solver).
- **Phase B**: Sprint 6.4 (WebGPU 1M overview optimization).
- **Phase C**: Sprints 6.5 + 6.6 in parallel (AI extensions & Enterprise SSO).
- **Phase D**: Sprint 6.3 (Stage 2 Cloud Infra) activated upon triggering R-99 commercial event.
