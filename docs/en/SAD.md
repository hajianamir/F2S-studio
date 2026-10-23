# Software Architecture Document (SAD) — As-Built
**Fire Protection Design & Simulation Platform**
*Version 1.0.0 (MVP) - NFPA 13 / NFPA 72 Compliance Engine*

---

## 1. Executive Summary
The Fire Protection Design & Simulation Platform is an integrated, cloud-native engineering platform for fire suppression (sprinkler/standpipe/water mist) and fire alarm design, hydraulic calculations, rule compliance verification, and BIM/IFC integration.

## 2. As-Built Architecture & Technology Stack
- **Computational Core (`core/`)**: C++20 dynamic shared library (`libfire_protection_core.so`). Implements Hazen-Williams, Darcy-Weisbach, Hardy Cross loop solver, and NFPA 72 NAC voltage drop & battery calculations with C ABI export.
- **Backend Service (`backend/`)**: .NET 8 ASP.NET Core REST API wrapping C++ core via P/Invoke (`NativeMethods.cs`). Includes OpenAPI 3.1 specs, async job queue polling, and xBIM-based IFC4 BIM import/export.
- **Rule Engine (`core/rules/`)**: Declarative versioned JSON rulesets (`NFPA13-2022.json`, `NFPA72-2022.json`) decoupling standard logic from binary releases.
- **3D Web UI (`web/`)**: React 18 + Three.js + TypeScript SPA with WebGL rendering of pipe geometry, pressure heatmaps, BCF 3D annotation pinning, and English/Persian RTL toggle.

## 3. Technical Risk Probes Analysis & Safeguards

### 3.1 Hardy Cross Convergence & Edge Cases
- **Near-Zero Flow & Division by Zero**: Initialized with non-zero directional seed flow ($Q_0 = 10.0$ GPM) to eliminate $1.85 \cdot h_f / Q$ zero-division.
- **Damped Loop Adjustment**: Damping parameter ($α = 0.10$) applied to delta-Q corrections prevents numerical oscillation in tightly coupled grid loops.
- **Divergence Protection**: Max iteration cap (200) sets `success = false` and returns explicit warning messages if tolerance ($ΔQ < 0.01$ GPM) is not met within iteration limit.

### 3.2 Native AOT & P/Invoke Marshalling
- `NativeMethods.cs` utilizes direct `[DllImport("libfire_protection_core")]` with explicit `CallingConvention.Cdecl` and manual `Marshal.PtrToStringAnsi` string memory management via `fp_free_string` to avoid reflection dependency during Native AOT trim pass.

### 3.3 Three.js Rendering at Scale
- Geometry instantiation and material sharing across pipe cylinders and sprinkler cones reduce draw calls. Level of Detail (LOD) and frustum culling strategies are defined for Phase 2 scaling beyond 100k elements.

### 3.4 NFPA 72 Battery Calculation Parameters
- Implements NFPA 72 §10.6.7 formulas: $Ah_{total} = (I_{standby} \cdot t_{standby} + I_{alarm} \cdot t_{alarm}) \cdot 1.20$, incorporating standard 20% safety margin ($1.20$ multiplier).

## 4. Test Suite Coverage Metrics
- **C++ Computational Core**: 100% CTest pass rate across unit tests and benchmark golden tests.
- **Backend API**: 100% xUnit test pass rate on interop bindings and domain models.
- **Frontend SPA**: Clean TypeScript compilation (`tsc`) and Vite production bundle build.
