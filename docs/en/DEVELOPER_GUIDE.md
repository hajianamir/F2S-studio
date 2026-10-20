# Developer Guide

---

## 1. Prerequisites
- GCC / G++ >= 13 (C++20 support)
- CMake >= 3.20
- .NET SDK 8.0 / 10.0
- Node.js >= 20

## 2. Building & Testing C++ Core
```bash
cd core
mkdir build && cd build
cmake ..
make
ctest --output-on-failure
```

## 3. Building & Running Backend
```bash
cd backend/src/Api
dotnet run
```

## 4. Building & Running Frontend
```bash
cd web
npm install
npm run build
```
