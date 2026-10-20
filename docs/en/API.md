# API Specification
**Fire Protection Platform - OpenAPI 3.1 Reference**

---

### Endpoints

#### `GET /api/health`
Returns health status of the API backend and version info.

#### `POST /api/hydraulics/calculate`
Dispatches a hydraulic calculation job to the native C++ core.
- **Request Body**: JSON representing network nodes and pipes per `network.schema.json`.
- **Response**: `{ "jobId": "string", "status": "Queued", "pollingUrl": "/api/jobs/{jobId}" }`

#### `GET /api/jobs/{jobId}`
Polls status and result of a long-running calculation job.

#### `GET /api/units/gpm-to-lpm?gpm={value}`
Converts flow rate from US Customary (GPM) to SI Units (L/min).
