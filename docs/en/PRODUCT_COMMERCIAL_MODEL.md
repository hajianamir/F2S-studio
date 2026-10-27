# Product, Commercial & Customer Operations Architecture (Option C)
**Fire Protection Design & Simulation Platform**

---

## 1. Commercial Pricing Tiers, Small-Team Tier & Trial Seal Security (R-96, R-103, R-104 Resolved)
- **14-Day Free Trial Tier ($0 / 14 Days — R-96 & R-104 Resolved)**:
  - Includes 1 active project, 1 GB storage, full C++ hydraulic calculations, and WebGL viewer.
  - Includes 1 test PE seal execution stamped with a non-removable red visual watermark: *"TRIAL VERSION — NOT VALID FOR MUNICIPAL AHJ SUBMITTAL"*.
  - *Cryptographic Distinctness (R-104 Resolved)*: Trial seals are signed with a distinct trial-only KMS key (`trial_kms_key`) with signature metadata marked `"TRIAL_NON_SUBMITTAL"`. Verification API returns `TRIAL` status regardless of visual PDF watermark state.
- **Professional Engineer (PE) Plan ($499 / month per seat)**: Solo PE license for individual consultants.
- **Small-Team Plan ($349 / month per seat — R-103 Resolved)**: Designed for 2 to 4 seat firms, bridging solo PE and Enterprise tiers.
- **Enterprise Firm Plan ($2,499 / month per firm — $250/seat at 10 seats)**: Includes up to 10 seats ($199/mo per additional seat), dedicated schema isolation, custom domain, and priority support.
- **Beta Firm Transition Terms & Unconditioned Perpetual Discount (R-97 Resolved)**:
  - Beta Firms A & B receive an **unconditioned perpetual 50% discount** off list price on their selected tier ($1,249/mo Enterprise or $174.50/seat Team) as consideration for early validation and MOU partnership.
  - *Communication Status*: Formal written confirmation of the 50% perpetual commercial discount was transmitted to the principals of Beta Firms A & B alongside the Phase 4/5 roadmap updates, strengthening beta firm alignment prior to the January 2027 live portal onboarding.
- **Target Customer Positioning**: Designed for AEC/FPE firms running 3+ disconnected tools who value an integrated workflow saving 15+ hours/project over single-purpose desktop tools.

---

## 2. Inclusions & Quotas Matrix per Tier

| Feature / Resource | Free Trial (14 Days) | Solo PE ($499/mo) | Small Team ($349/seat/mo) | Enterprise ($2,499/mo) |
|---|---|---|---|---|
| **Active Projects** | 1 Project | 15 Projects | 50 Projects Shared | Unlimited |
| **BIM Storage Quota** | 1 GB | 25 GB / seat | 100 GB Shared | 500 GB Shared |
| **Hydraulic Calculations** | Unlimited | Unlimited | Unlimited | Unlimited |
| **Digital PE Seal Signings** | 1 Cryptographic Trial | 25 Signings / mo | 75 Signings / mo Shared | Unlimited |
| **AI Layout Optimization Runs** | 3 Test Runs | 20 Runs / mo | 60 Runs / mo Shared | 100 Runs / mo |

---

## 3. Stage 2 Trigger Precedence, SLA & Modal Logging (R-95, R-99, R-101, R-102 Resolved)

### Stage 2 Infrastructure Activation Trigger Precedence (R-99 Resolved)
- Stage 2 EKS Multi-AZ, CloudHSM, and WORM storage activation is **event-driven**.
- **Trigger Precedence**: Activated upon reaching **10 active commercial firm tenants OR $300,000 ARR, whichever comes first**. Load (10 tenants) and revenue ($300k) represent independent signals justifying Stage 2 infra expansion.

### Stage 1 SLA Adjustment & Service Credits (R-95 Resolved)
- **Stage 1 SLA Target**: **99.5% Uptime** for core API endpoints (~3.6h allowable downtime/month).
- **SLA Remedy Credits**:
  - Availability 99.0% – 99.49%: **10% monthly subscription credit**.
  - Availability < 99.0%: **25% monthly subscription credit**.

### Point-of-Signing Modal, Audit Logging & GDPR Note (R-102 Resolved)
- When a PE clicks *"Sign and Seal"*, a mandatory confirmation modal appears:
  > **Legal PE Responsibility Confirmation**:
  > *"By affixing your digital seal, you confirm that you have independently reviewed and verified all calculation inputs, hydraulic network configurations, and output reports, accepting 100% professional liability under your engineering license."*
- **Audit Logging**: Modal acceptance is logged with timestamp, user ID, project revision hash, and IP address, retained for 7 years in immutable audit storage.
- **GDPR Note**: IP address 7-year retention applies to US Stage 1. GDPR DPIA review is required prior to future EU deployment.
- Legal terms specification documented in `docs/en/LEGAL_TERMS.md` (R-101 Resolved).
