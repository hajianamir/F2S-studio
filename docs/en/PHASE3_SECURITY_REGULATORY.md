# Phase 3 Security, Regulatory & AI Position Papers
**Fire Protection Design & Simulation Platform**

---

## 1. R-12 Position Paper: AI-Generated Layouts & AHJ Acceptance / PE Sign-Off

### 1.1 Regulatory & PE Liability Framework
- **Advisory Role**: Generative AI layout suggestions are strictly **Advisory Design Suggestions**. AI algorithms do not possess engineering stamps or professional liability insurance.
- **PE Sign-Off Mandatory**: Every AI-optimized sprinkler layout must be explicitly reviewed, validated, and stamped by a licensed Professional Engineer (PE) prior to submittal to Authority Having Jurisdiction (AHJ) plan review.
- **Audit Logging**: The platform records an immutable revision entry when an AI-generated layout is accepted, modified, or stamped by the PE.

---

## 2. R-13 Position Paper: IoT Ingestion Security & Attack Surface Architecture

### 2.1 Read-Only Isolation Architecture
- **Unidirectional Data Flow**: The IoT sensor stream ingestion pipeline (MQTT / InfluxDB) operates in a strictly **Read-Only Telemetry Ingestion Mode**.
- **No Ingestion Write-Back**: Real-time sensor pressure and flow streams cannot modify underlying BIM network topology, pipe sizing, or compliance calculations.
- **Security Protocols**: All sensor streams require TLS 1.3 encryption, mTLS client certificates, and strict RBAC authorization.
