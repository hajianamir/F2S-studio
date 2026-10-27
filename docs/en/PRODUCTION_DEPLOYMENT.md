# Production Deployment & Multi-Tenancy Architecture (Option C)
**Fire Protection Design & Simulation Platform**

---

## 1. Cloud-Native Topology & Multi-Tenancy Design
- **Infrastructure Topology**: Deployed on managed Kubernetes (AWS EKS / GCP GKE) with multi-AZ high availability.
- **Database & Tenant Isolation**:
  - *PostgreSQL*: Schema-per-tenant isolation for transactional design data, calculation state, and user management.
  - *MongoDB*: Isolated collections for BIM IFC4 models, geometries, and BCF annotations.
  - *TimescaleDB / InfluxDB*: Multi-tenant time-series database for IoT sensor telemetry.
- **Security & Data Residency**:
  - TLS 1.3 in transit; AES-256 encryption at rest with KMS tenant-managed keys.
  - Compliance with SOC2 Type II, ISO 27001, and AEC client confidentiality requirements.

---

## 2. Backup, Disaster Recovery & SLAs
- **Recovery Point Objective (RPO)**: $< 15 \\text{ minutes}$ via continuous WAL archiving.
- **Recovery Time Objective (RTO)**: $< 1 \\text{ hour}$ with automated failover.
- **Backup Schedule**: Daily automated snapshots retained for 30 days; monthly immutable archives retained for 7 years (matching engineering PE liability retention windows).

---

## 3. PE Onboarding & Firm Provisioning Workflow
1. **Firm Account Provisioning**: Automated tenant schema creation, custom domain mapping (`firm-a.fireplatform.com`), and KMS key pair generation.
2. **User & License Management**: Role-Based Access Control (RBAC) supporting Admin, Principal PE, Design Engineer, and Reviewer roles.
3. **Digital Signature Integration**: Secure PE electronic seal vault with SHA-256 hash generation and HSM integration.
