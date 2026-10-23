# Phase 3 Deep Security, Regulatory, AI Frameworks & MVP Acceptance Criteria
**Fire Protection Design & Simulation Platform**

---

## 1. R-12 Deep Operational Position Paper: AI-Generated Layouts & AHJ Acceptance / PE Sign-Off

### 1.1 Mandatory PE Review & Liability Framework
- **Advisory Role**: Generative AI layout suggestions are strictly classified as **Advisory Design Suggestions**. AI models do not hold engineering licenses or professional liability insurance.
- **PE Sign-Off Mandatory**: Every AI-optimized sprinkler layout must be explicitly reviewed, validated, and stamped by a licensed Professional Engineer (PE) prior to submittal to Authority Having Jurisdiction (AHJ) plan review.
- **Liability Disclaimer**: Terms of Service and generated export reports prominently display: *"Notice: AI-generated layouts are advisory suggestions. The Engineer of Record (PE) assumes full professional responsibility for layout review, rule compliance verification, and AHJ submittal."*

### 1.2 Audit Log Structure & Model Versioning
Every AI layout interaction records an immutable audit log entry containing:
```json
{
  "timestamp": "2026-10-23T09:30:00Z",
  "ai_model_version": "GenerativeSprinkler-v1.4.2",
  "pe_user_id": "PE-10492-CA",
  "action": "ACCEPT_WITH_MODIFICATIONS",
  "input_topology_hash": "a8f9c3...",
  "suggested_pipe_length_ft": 420.5,
  "final_pe_pipe_length_ft": 435.0,
  "rejection_or_modification_reason": "Adjusted branch line 2 to clear structural steel beam B-102."
}
```

### 1.3 AHJ Submittal Output Policy
- **Permit Submittal Packages**: AHJ plan submittal packages render **ONLY the final PE-stamped design**. AI alternatives and discarded suggestions are excluded from permit drawings to avoid reviewer confusion during municipal plan review.

---

## 2. R-13 Deep Operational Position Paper: IoT Ingestion Security & Threat Model

### 2.1 Threat Model & Security Controls
1. **Unidirectional Read-Only Telemetry Isolation**: The IoT sensor stream ingestion pipeline (MQTT / InfluxDB) operates in a strictly **Read-Only Ingestion Mode**. Telemetry streams are physically isolated and cannot modify design BIM data, pipe sizing, or hydraulic calculations.
2. **Data-at-Rest Encryption & GDPR Compliance**: Sensor time-series data is encrypted at rest using AES-256 with rotation keys. No personally identifiable information (PII) is linked to pressure/flow sensor readings.
3. **Rate Limiting & Payload Sanitization**: Ingestion endpoints enforce per-device rate limiting (max 10 Hz) and JSON Schema payload validation. Anomaly payloads are quarantined without interrupting API availability.
4. **Sensor Spoofing Mitigation**: Divergent pressure readings (>30% variance against adjacent peer sensors) trigger a `SensorAnomalyWarning` UI alert without altering design safety margins.
5. **Blast Radius Isolation**: Compromise of a telemetry ingestion node is confined to the time-series datastore and cannot breach CAD/BIM model databases or PE design files.

---

## 3. R-14 AI MVP Acceptance Criteria & Measurable Objective

### 3.1 Single Optimization Objective & Measurable Metric
- **Optimization Objective**: **Minimize Total Pipe Run Length (Material Cost)** subject to 100% NFPA 13 coverage compliance.
- **Fixed Network Topology**: Standard 50 ft x 100 ft Light Hazard office layout (100k sq ft total coverage).
- **Target Performance**: Achieve **>= 8.0% reduction in total pipe footage** compared to standard manual grid layout while satisfying 100% of NFPA 13 spacing and hydraulic pressure rules.

---

## 4. Phase 3 Roadmap Amendments: AHJ Quality & User Testing Sprints

### 4.1 Sprint 3.4: AHJ Report Quality Verification (R-15)
- Validation of formatted calculation reports (`report.pdf` / `report.json`) against published Municipal Fire Department AHJ plan review checklist requirements.

### 4.2 Sprint 3.5: Designer-in-the-Loop Usability Testing (R-16)
- Usability testing with 5 active PE fire protection designers evaluating UI workflow speed, BCF pinning, and 3D viewport responsiveness.


## 5. R-12 & R-13 Final Clarifications & Operational Protocols

### 5.1 R-12 Internal-vs-AHJ View Rendering & Rejected Suggestion Audit
- **Internal Review Viewport**: Displays full AI suggestion geometry, alternative pipe routing candidates, rejected proposals, and PE modification logs.
- **AHJ Submittal Package**: Renders **ONLY the final PE-stamped layout**, accompanied by an appendix statement certifying PE sign-off.
- **Rejected Suggestion Audit**: Rejected AI proposals are explicitly recorded in the audit trail (`action: "REJECTED"`, `reason: "Structural beam interference"`).

### 5.2 R-13 Telemetry Access Audit, Retention Policy & Incident Notification
- **Access Audit Logging**: Every query against sensor telemetry stores a logged audit record containing `user_id`, `timestamp`, `queried_sensor_id`, and `purpose_code`.
- **Data Retention Policy**: Raw time-series readings retained for 90 days in primary hot storage, archived to encrypted AES-256 cold storage for 3 years, and purged automatically per GDPR data minimization rules.
- **Incident Response Runbook**: Any detected ingestion breach or mTLS certificate failure triggers instant email/SMS notifications to the **Project Owner**, **Engineer of Record (PE)**, and **Client Security Officer**.

### 5.3 R-14 AI Baseline Definition & Compliance Scope Reframe
- **Baseline Definition**: The optimization baseline is defined as **the platform's current non-AI rule-engine default layout** for the 100k sq ft Light Hazard reference model.
- **Reframed Compliance Claim**: *"Minimum 8.0% pipe run footage reduction achieved compared to the platform's non-AI default layout, subject to 100% compliance with the 30+ implemented NFPA 13 (2022) digital rule engine clauses."*
