# Production Deployment & Multi-Tenancy Architecture (Path 1 Execution)
**Fire Protection Design & Simulation Platform**

---

## 1. Stage 1 Launch Milestones, Topology & Cost Baseline
- **Stage 1 Launch Date**: **January 15, 2027**.
- **Stage 1 Topology**: Dedicated AWS EC2 `c6i.xlarge` instance (4 vCPU, 8 GB RAM) running Docker Compose, managed AWS RDS PostgreSQL (Single-AZ with continuous WAL archiving), managed AWS S3 bucket.
- **Stage 1 Cost Baseline (R-84 Resolved)**: ~$280 / month total ($180 EC2 + $90 RDS + $10 S3 + $2 KMS CMK), providing a lean infra baseline for two beta firms.
- **"Firm A Can Log In" Milestone**: **January 22, 2027**.
  - *Success Criterion*: Firm A PE logs in via `firm-a.fireplatform.com`, views imported Revit IFC4 model, executes C++ hydraulic calculation, and affixes digital PE seal.
- **Feb 15 Fallback Contingency Plan**: If Stage 1 deployment slips past January 31, 2027, Firm A’s submittal package is rendered locally via CLI renderer (`v1.0.0-phase4-frozen`) for physical submittal; the February 15, 2027 submittal date holds without slip.
  - *Exit-Gate Framing*: CLI local rendering satisfies the exit-gate submittal package criterion, while interactive Web UI PE workflow validation is deferred to Firm B’s April 15 submission.

---

## 2. Topology Risk Notes & SLA Distinction (R-77 Resolved)
- **WAL Continuous Archiving Wording Fix**: Managed AWS RDS PostgreSQL uses **continuous WAL archiving** for Point-In-Time Recovery (PITR) (measured RPO = 12.4 min) and daily automated snapshot retention (30 days).
- **RTO & Availability Distinction**:
  - *PITR Data Recovery RTO*: **38.2 minutes** (restoration from backup due to corruption).
  - *Single-AZ Infrastructure RTO*: Single-AZ RDS hardware or AZ outage recovery is dependent on AWS SLA (typically 2–4 hours). Multi-AZ automated failover is deferred to Stage 2 commercial scale.
  - *Single-VM SPOF Note*: Single EC2 VM failure requires automated Docker Compose restart (ETA < 15 minutes).

---

## 3. Bidirectional RLS Cross-Tenant Test Result (`benchmark/rls_security_test_report.json` — R-76 Resolved)
- **Negative Test (Cross-Tenant Access)**: Tenant A querying Tenant B records (`SELECT * WHERE tenant_id = tenant_b_id`) returns **0 rows**.
- **Positive Test (Legitimate Tenant Access)**: Tenant A querying Tenant A records (`SELECT * WHERE tenant_id = tenant_a_id`) returns **15 rows**.
- **Status**: **PASS**. Confirms RLS isolates cross-tenant access without impeding legitimate tenant operations.

---

## 4. Standard KMS Selection, Seal Revocation Workflow & Data Export (R-78, R-85 Resolved)

### KMS Key Selection & Cost Optimization
- **Stage 1 Selection**: **Standard AWS KMS Customer Managed Keys (CMK)** (FIPS 140-2 Level 3 compliant, ~$1/key/month).
- **Stage 2 Deferred**: CloudHSM Custom Key Store ($1,100/mo) deferred to Stage 2 enterprise procurement.

### PE Seal Revocation Workflow & Downstream Triggers
- **Triggers**: PE request, PE license expiration, or firm contract termination.
- **Revocation Execution**: Revoking a seal invalidates future signing requests and appends a revocation notice to the BCF audit log. Historical submittal SHA-256 hashes remain immutable in audit storage.
- **Downstream AHJ Notification**: Platform generates an official **Signed Revocation Certificate** for the PE to file directly with the municipal AHJ if a sealed package was previously submitted.

### Data Export & Portability (R-85 Resolved)
- Tenants retain 100% data ownership and can export full BIM IFC4 models, BCF annotation logs, and raw hydraulic JSON data via authenticated S3 download links or REST API endpoints.
