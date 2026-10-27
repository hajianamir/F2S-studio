# Product, Commercial & Customer Operations Architecture (Option C)
**Fire Protection Design & Simulation Platform**

---

## 1. Commercial Pricing Tiers, Small-Team Tier & Trial Watermark (R-96, R-103 Resolved)
- **14-Day Free Trial Tier ($0 / 14 Days — R-96 Resolved)**: Includes 1 active project, 1 GB storage, full C++ hydraulic calculations, and WebGL viewer. Includes 1 test PE seal execution stamped with a non-removable red watermark: *"TRIAL VERSION — NOT VALID FOR MUNICIPAL AHJ SUBMITTAL"*.
- **Professional Engineer (PE) Plan ($499 / month per seat)**: Solo PE license for individual consultants.
- **Small-Team Plan ($349 / month per seat — R-103 Resolved)**: Designed for 2 to 4 seat firms, bridging solo PE and Enterprise tiers.
- **Enterprise Firm Plan ($2,499 / month per firm — $250/seat at 10 seats)**: Includes up to 10 seats ($199/mo per additional seat), dedicated schema isolation, custom domain, and priority support.
- **Beta Firm Transition Terms & Discount Mechanism (R-97 Resolved)**: Beta Firms A & B receive a **perpetual 50% percentage discount** off list price on their selected tier (e.g. $1,249/mo Enterprise or $174.50/seat Team) contingent on maintaining active PE feedback and case-study permissions.
- **Target Customer Positioning**: Designed for AEC/FPE firms running 3+ disconnected tools who value an integrated workflow saving 15+ hours/project over single-purpose desktop tools.

---

## 2. Inclusions & Quotas Matrix per Tier

| Feature / Resource | Free Trial (14 Days) | Solo PE ($499/mo) | Small Team ($349/seat/mo) | Enterprise ($2,499/mo) |
|---|---|---|---|---|
| **Active Projects** | 1 Project | 15 Projects | 50 Projects Shared | Unlimited |
| **BIM Storage Quota** | 1 GB | 25 GB / seat | 100 GB Shared | 500 GB Shared |
| **Hydraulic Calculations** | Unlimited | Unlimited | Unlimited | Unlimited |
| **Digital PE Seal Signings** | 1 Watermarked | 25 Signings / mo | 75 Signings / mo Shared | Unlimited |
| **AI Layout Optimization Runs** | 3 Test Runs | 20 Runs / mo | 60 Runs / mo Shared | 100 Runs / mo |

---

## 3. Legal Specification Labeling, SLA & Modal Logging (R-95, R-101, R-102 Resolved)

### Legal Requirements Specification Labeling (R-101 Resolved)
- `docs/en/LEGAL_TERMS.md` and `docs/fa/LEGAL_TERMS_FA.md` are formally labeled as **"Legal Requirements Specification for External Counsel Drafting"**. Final customer binding contracts will be drafted by commercial specialized legal counsel prior to converting Firm A/B to paying status.

### Stage 1 SLA Adjustment & Service Credits (R-95 Resolved)
- **Stage 1 SLA Target**: **99.5% Uptime** for core API endpoints (~3.6h allowable downtime/month).
- **SLA Remedy Credits**:
  - Availability 99.0% – 99.49%: **10% monthly subscription credit**.
  - Availability < 99.0%: **25% monthly subscription credit**.

### Point-of-Signing Modal & Immutable Audit Logging (R-102 Resolved)
- When a PE clicks *"Sign and Seal"*, a mandatory confirmation modal appears:
  > **Legal PE Responsibility Confirmation**:
  > *"By affixing your digital seal, you confirm that you have independently reviewed and verified all calculation inputs, hydraulic network configurations, and output reports, accepting 100% professional liability under your engineering license."*
- **Audit Logging**: Every modal acceptance is logged with timestamp, user ID, project revision hash, and IP address, retained for 7 years in immutable storage.
