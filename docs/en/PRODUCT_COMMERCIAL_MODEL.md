# Product, Commercial & Customer Operations Architecture (Option C)
**Fire Protection Design & Simulation Platform**

---

## 1. Commercial Pricing Model & Unit Economics
- **Professional Engineer (PE) Plan**: **$499 / month per seat** (or $4,990 / year prepaid). Includes full hydraulic engine, rule engine compliance checks, WebGL 3D viewer, and 5 GB BIM storage per user.
- **Enterprise Firm Plan**: **$2,499 / month per firm** (includes up to 10 seats, $199/month per additional seat). Includes dedicated schema isolation, custom subdomain, PE seal vault, BCF 3D coordination, and priority support.
- **AHJ / Municipal License**: **$0 (Freemium Reviewer License)** for municipal plan examiners (LA County, FDNY, Chicago) to verify digital submittal hashes, BCF 3D annotations, and hydraulic calculation inputs.
- **Unit Economics Baseline**: Stage 1 infra cost ($280/mo) is fully cleared by a single Enterprise firm or 1 Professional Engineer subscription, generating $> 85\%$ gross margin.

---

## 2. Customer Onboarding & Self-Service Provisioning Flow
1. **Self-Service Sign-Up**: Admin PE signs up via web portal, verifies PE license credentials, and creates firm tenant workspace.
2. **Automated Tenant Provisioning**: System provisions dedicated PostgreSQL schema, S3 bucket, Route53 subdomain, and KMS key pair in $< 3 \\text{ minutes}$.
3. **PE Seal Onboarding & Vault Activation**: PE uploads electronic seal graphic, sets TOTP MFA, and verifies digital signature test page.
4. **BIM & Project Import**: Guided import wizard for Revit IFC4 models, auto-detecting pipe networks, sprinklers, and structural obstacles.

---

## 3. Support Model & Engineering SLA
- **Tier 1 (Customer Success / General Onboarding)**: $< 8 \\text{ hour}$ response time for billing, user accounts, and UI navigation questions.
- **Tier 2 (Professional Engineer Support)**: Staffed by licensed FPEs. $< 4 \\text{ hour}$ response time during business hours for hydraulic calculation discrepancy questions, NFPA clause interpretation, or AHJ submittal format queries.
- **Tier 3 (Systems Engineering)**: $< 1 \\text{ hour}$ response time for critical platform outages or database access failures.

---

## 4. Terms of Service, Legal Liabilities & SLA
- **Platform Liability Boundary**: The platform acts strictly as a **computational and drafting aid**. Final engineering calculations, code compliance, and submittal responsibility remain 100% with the Professional Engineer of Record who seals the document.
- **Service Level Agreement (SLA)**: **99.9% Uptime SLA** backed by service credits for Stage 2 commercial customers.
