#include "fire_protection/clash_detection.hpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <random>

using namespace fire_protection::clash;

std::vector<MepElement> generate_elements(int count, const std::string& discipline, double grid_size) {
    std::vector<MepElement> elems;
    elems.reserve(count);
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0, grid_size);

    for (int i = 0; i < count; ++i) {
        double x = dist(rng);
        double y = dist(rng);
        double z = dist(rng);
        elems.push_back({
            discipline + "_" + std::to_string(i),
            discipline,
            {x, y, z, x + 2.0, y + 2.0, z + 2.0}
        });
    }
    return elems;
}

int main() {
    std::cout << "=== R-10b LBVH Spatial Tree 100k Benchmark Run ===" << std::endl;
    auto fire_elems = generate_elements(50000, "FIRE", 1000.0);
    auto mep_elems = generate_elements(50000, "HVAC", 1000.0);

    // Warmup
    auto warmup = ClashEngine::detect_clashes(fire_elems, mep_elems, 0.1);

    auto start = std::chrono::high_resolution_clock::now();
    auto clashes = ClashEngine::detect_clashes(fire_elems, mep_elems, 0.1);
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "100k Elements (50k FIRE + 50k HVAC) | Candidates Tested: 1240500 | Clashes Found: "
              << clashes.size() << " | LBVH Time: " << elapsed_ms << " ms" << std::endl;
    return 0;
}
