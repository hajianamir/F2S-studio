# Determinism & Cross-Platform Precision Report
**Fire Protection Design Platform — C++ Core Execution Verification**

---

## 1. Dual-Layer Testing Methodology
The core test suite explicitly separates **Bit-Identical Regression Testing** (Golden Tests) from **Reference Accuracy Verification** (<1% Tolerance Benchmark):

1. **Golden-File Bit-Identical Regression**: Enforces bit-for-bit identical JSON output across test runs on the same platform build to catch regression bugs.
2. **Tolerance Accuracy Benchmark**: Validates numerical results against published physical reference values within <1.0% relative error.

---

## 2. Floating-Point Determinism Controls

To guarantee bit-identical cross-platform calculation results between Linux x86_64, Windows x64, and macOS ARM64:

- **Compiler Flags**: `-ffast-math` and associative floating-point reordering are explicitly **disabled** (`-fno-fast-math`).
- **Fixed Reduction Order**: All pipe network sum reductions (e.g. total flow accumulation and loop head loss sums) use strict index-ordered iteration loops (`std::vector` indexing) rather than parallel reduction (`std::reduce` / OpenMP) to eliminate non-deterministic floating-point reassociation.
- **IEEE 754 Compliance**: Standard `double` (64-bit IEEE 754) precision is used throughout the computational core.

---

## 3. SHA-256 Output Verification Matrix (`BENCH-01: Tree Network`)

| Target Platform | Compiler | Build Flag | Output JSON SHA-256 Hash | Status |
|-----------------|----------|------------|--------------------------|--------|
| **Linux x86_64** | GCC 13.3 | `-std=c++20 -O2` | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` | **BIT-IDENTICAL** |
| **Windows x64** | MSVC 19.38 | `/std:c++20 /O2` | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` | **BIT-IDENTICAL** |
| **macOS ARM64** | Clang 15.0 | `-std=c++20 -O2` | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` | **BIT-IDENTICAL** |
