# Software Architecture Document (SAD)
**Fire Protection Design & Simulation Platform**
*Version 1.0.0 (MVP) - NFPA 13 / NFPA 72 Compliance Engine*

---

## 1. Executive Summary & Vision
The Fire Protection Design & Simulation Platform is an integrated, cloud-native, open-architecture engineering application designed for fire suppression (sprinkler, standpipe, water mist) and fire alarm system design, hydraulic calculation, rule compliance verification, and BIM/IFC integration.

## 2. High-Level Architecture
The platform adheres to a modular Clean Architecture / CQRS pattern with decoupled domain layers:
- **Computational Core (`core/`)**: High-performance C++20 dynamic library exposed via C ABI (`extern "C"`). Implements Hazen-Williams, Darcy-Weisbach, Hardy Cross loop solver, and NFPA 72 NAC/battery equations.
- **Backend Service (`backend/`)**: .NET 8 ASP.NET Core REST API wrapping C++ core via P/Invoke. Provides OpenAPI 3.1 specifications, async job queues, and xBIM-based IFC4 BIM import/export.
- **Rule Engine (`core/rules/`)**: Declarative versioned JSON rulesets (`NFPA13-2022`, `NFPA72-2022`) decoupling standard logic from software updates.
- **Web 3D Viewport (`web/`)**: React + Three.js + TypeScript WebGL viewport rendering color-coded pressure heatmaps, pipe geometry, and BCF 3D annotation pins with EN/FA RTL toggle.

## 3. Data Flow & Interop Strategy
```
+-------------------+       REST / JSON       +-----------------------+
|  React 3D Web UI  | <=====================> | .NET 8 Web API        |
+-------------------+                         +-----------------------+
                                                          ||
                                                     P/Invoke (C ABI)
                                                          ||
                                                          \/
                                              +-----------------------+
                                              | C++20 Core Library    |
                                              +-----------------------+
```

## 4. Key Performance & Quality Attributes
- **Precision**: Hydraulic calculations matched against benchmark published reference cases within <1% error margin.
- **Determinism**: Zero non-deterministic floating-point reduction across platforms.
- **Auditability**: JSON-serialized calculation run logs linked with project revision IDs.
