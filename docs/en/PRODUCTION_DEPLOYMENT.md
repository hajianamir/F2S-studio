# Production Deployment & Multi-Tenancy Architecture (Path 1 Execution)
**Fire Protection Design & Simulation Platform**

---

## 1. Stage 1 Launch Milestones, Topology & Cost Baseline
- **Stage 1 Launch Date**: **January 15, 2027**.
- **Stage 1 Go/No-Go Decision Point (R-87 Resolved)**: **January 8, 2027**.
  - *Pass Criteria*: Automated smoke test suite green (6/6 pass), dry-run login pass, zero blocking bugs, and **actual PITR restore test verified on live Stage 1 RDS instance (R-90 Resolved)**.
  - *Fallback Trigger*: Any blocking bug or SLA failure unresolved by Jan 8 defers launch 1 week or triggers Feb 15 CLI local fallback.
- **Stage 1 Topology**: Dedicated AWS EC2 `c6i.xlarge` instance (4 vCPU, 8 GB RAM) running Docker Compose, managed AWS RDS PostgreSQL (Single-AZ with continuous WAL archiving), managed AWS S3 bucket.
- **Stage 1 Cost Baseline (R-84 Resolved)**: ~$280 / month total ($180 EC2 + $90 RDS + $10 S3 + $2 KMS CMK), providing a lean infra baseline for two beta firms.
- **"Firm A Can Log In" Milestone**: **January 22, 2027**.
  - *Success Criterion*: Firm A PE logs in via `firm-a.fireplatform.com`, views imported Revit IFC4 model, executes C++ hydraulic calculation, and affixes digital PE seal.
- **Feb 15 Fallback Contingency Plan & Exit-Gate Framing (R-86 Resolved)**:
  - If Stage 1 deployment slips past January 31, 2027, Firm A’s submittal package is rendered locally via CLI renderer (`v1.0.0-phase4-frozen`) for physical submittal; the February 15, 2027 submittal date holds without slip.
  - *Exit-Gate Framing*: CLI local rendering satisfies the exit-gate submittal package criterion, while interactive Web UI PE workflow validation is deferred to Firm B’s April 15 submission.

---

## 2. Stage 1 Observability, Alerting & End-to-End Downtime SLA (R-79, R-91 Resolved)
- **End-to-End Downtime SLA Breakdown (R-91 Wording Fix)**:
  - *PITR Database Restoration Time*: **38.2 minutes** (measured database replay time).
  - *Detection Time*: Up to **10.0 minutes** (worst case for 2 consecutive 5-minute ping failures).
  - *Total End-to-End Failure-to-Recovery Time*: **~48.2 minutes** total (strictly satisfies $< 1 \\text{ hour}$ downtime SLA).
- **Minimal Observability Setup (<$5/mo)**:
  - *CloudWatch Alarms*: EC2 CPU > 80% for 10 min, RDS storage < 10% free.
  - *RDS Backup Failure Alarm*: Triggers immediately if daily WAL snapshot fails.
  - *Synthetic Ping*: Automated healthcheck ping to `https://firm-a.fireplatform.com/api/health` every 5 minutes; alerts via SMS/Email after 2 consecutive failures. Application-level P95 monitoring deferred to Stage 2.
- **Topology Risk & Availability Notes**:
  - *Single-AZ Infrastructure RTO*: Single-AZ RDS hardware or AZ outage recovery is dependent on AWS SLA (typically 2–4 hours). Multi-AZ automated failover is deferred to Stage 2.
  - *Single-VM SPOF Note*: Single EC2 VM failure requires automated Docker Compose restart (ETA < 15 minutes).

---

## 3. Pre-Launch Configuration Checklist (Auth Hygiene, DNS/SSL & Expanded Smoke Tests)
- **Auth Hygiene Policy & Step-Up Auth (R-88, R-92 Resolved)**:
  - *Password Policy*: Minimum 12 characters, requiring uppercase, lowercase, numbers, and symbols; no common password reuse.
  - *Account Lockout*: 5 consecutive failed login attempts trigger a 15-minute lockout to prevent brute-force attacks.
  - *Session Timeout*: 30 minutes of idle inactivity forces automatic re-authentication.
  - *Step-Up Authentication for PE Seal (R-92 Resolved)*: Seal signing requires mandatory TOTP re-verification immediately prior to affixing the PE digital seal, independent of active session state, preventing unauthorized seal usage if a device is left unattended.
  - *SSO Deferral*: Enterprise Single Sign-On (SSO / SAML / OIDC) is explicitly deferred to Phase 6.
- **DNS & SSL Provisioning**: AWS Route53 DNS + AWS ACM wildcard SSL certificate (`*.fireplatform.com`) with automated renewal.
- **Expanded Smoke Test Suite & Security Boundary Scope (`benchmark/stage1_smoke_test_report.json` — R-89, R-93 Resolved)**:
  - Executed via `scripts/stage1_smoke_test.py` covering 6/6 functional test cases:
    1. Healthcheck Endpoint (`GET /api/health` -> 200 OK)
    2. Auth API & TOTP MFA Verification (`POST /api/auth/login`)
    3. Core C++ Hydraulic Solver Interop (`POST /api/calc/hydraulic`)
    4. PDF Report Generator (`POST /api/report/generate`)
    5. KMS Digital Seal Vault Round-Trip Signing & Verification
    6. BCF 3D Annotation Persistence Test
  - *Scope Clarification (R-93 Resolved)*: The 6/6 smoke test verifies functional operation. Comprehensive security verification is managed separately via database RLS cross-tenant tests (complete), Sprint 5.3 external pentest audit (pending), and KMS seal vault authorization reviews.

---

## 4. Bidirectional RLS Cross-Tenant Test Result (`benchmark/rls_security_test_report.json` — R-76 Resolved)
- **Negative Test (Cross-Tenant Access)**: Tenant A querying Tenant B records (`SELECT * WHERE tenant_id = tenant_b_id`) returns **0 rows**.
- **Positive Test (Legitimate Tenant Access)**: Tenant A querying Tenant A records (`SELECT * WHERE tenant_id = tenant_a_id`) returns **15 rows**.
- **Status**: **PASS**. Confirms RLS isolates cross-tenant access without impeding legitimate tenant operations.

---

## 5. Standard KMS Selection & PE Seal Revocation Workflow (R-78, R-85 Resolved)
- **Stage 1 Selection**: Standard AWS KMS Customer Managed Keys (CMK) (FIPS 140-2 Level 3 compliant, ~$1/key/month).
- **PE Seal Revocation Workflow**:
  - *Triggers*: PE request, PE license expiration, or firm contract termination.
  - *Execution*: Revoking a seal invalidates future signing requests and appends a revocation notice to the BCF audit log. Historical submittal SHA-256 hashes remain immutable in audit storage.
  - *Downstream AHJ Notification*: Platform generates an official **Signed Revocation Certificate** for the PE to file directly with the municipal AHJ if a sealed package was previously submitted.
- **Data Export & Portability (R-85 Resolved)**: Tenants retain 100% data ownership and can export full BIM IFC4 models, BCF annotation logs, and raw hydraulic JSON data via authenticated S3 download links or REST API endpoints.
