# Production Deployment & Multi-Tenancy Architecture (Path 1 Execution)
**Fire Protection Design & Simulation Platform**

---

## 1. Stage 1 Launch Milestones, Fallback & Topology
- **Stage 1 Launch Date**: **January 15, 2027**.
- **Stage 1 Topology**: Dedicated AWS EC2 `c6i.xlarge` instance running Docker Compose, managed AWS RDS PostgreSQL (Single-AZ with daily automated snapshots), managed AWS S3 bucket.
- **"Firm A Can Log In" Milestone**: **January 22, 2027**.
  - *Success Criterion*: Firm A PE logs in via `firm-a.fireplatform.com`, views imported Revit IFC4 model, executes C++ hydraulic calculation, and affixes digital PE seal.
- **Feb 15 Fallback Contingency Plan**: If Stage 1 deployment slips past January 31, 2027, Firm A’s submittal package is rendered locally via CLI renderer (`v1.0.0-phase4-frozen`) for physical submittal; the February 15, 2027 submittal date holds without slip.

---

## 2. RLS Cross-Tenant Test Result (`benchmark/rls_security_test_report.json`)
- **Script**: `scripts/test_rls_security.py` (Automated cross-tenant leak test).
- **Test Result**: Tenant A context executed `SELECT * FROM hydraulic_calculations WHERE tenant_id = tenant_b_id`.
- **Outcome**: **Zero rows returned** at database level via PostgreSQL Row-Level Security (`app.current_tenant_id` session isolation). Verified!

---

## 3. HSM Choice & PE Seal Revocation Workflow
- **Stage 1 HSM Choice**: **AWS KMS Custom Key Store** (FIPS 140-2 Level 3 compliant). AWS CloudHSM dedicated cluster deferred to Stage 2 commercial scale.
- **PE Seal Revocation Workflow**:
  - *Authority*: PE of Record retains sole revocation authority over their electronic seal.
  - *Execution*: Revoking a seal immediately invalidates future signing requests and appends a revocation notice to the BCF audit log. Historical submittal package SHA-256 hashes remain immutable in audit storage for legal chain-of-custody verification.
