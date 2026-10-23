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

void run_benchmark(int fire_count, int mep_count, double grid_size) {
    auto fire_elems = generate_elements(fire_count, "FIRE", grid_size);
    auto mep_elems = generate_elements(mep_count, "HVAC", grid_size);

    // Warmup
    auto warmup = ClashEngine::detect_clashes(fire_elems, mep_elems, 0.1);

    auto start = std::chrono::high_resolution_clock::now();
    auto clashes = ClashEngine::detect_clashes(fire_elems, mep_elems, 0.1);
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Elements: Fire=" << fire_count << ", MEP=" << mep_count
              << " | Total Elements: " << (fire_count + mep_count)
              << " | Clashes Found: " << clashes.size()
              << " | Time: " << elapsed_ms << " ms" << std::endl;
}

int main() {
    std::cout << "=== R-10b Real C++ ClashEngine Benchmark Run ===" << std::endl;
    run_benchmark(100, 95, 100.0);      // ~195 elements
    run_benchmark(5000, 5000, 500.0);   // ~10,000 elements
    run_benchmark(50000, 50000, 1000.0); // ~100,000 elements
    return 0;
}
