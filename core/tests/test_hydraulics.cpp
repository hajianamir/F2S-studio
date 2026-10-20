#include "fire_protection/hydraulics.hpp"
#include "fire_protection/units.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace fire_protection;

void test_unit_conversions() {
    assert(std::abs(units::gpm_to_lpm(100.0) - 378.541) < 0.01);
    assert(std::abs(units::psi_to_bar(100.0) - 6.89476) < 0.01);
    assert(std::abs(units::inch_to_mm(2.0) - 50.8) < 0.01);
    std::cout << "[PASS] Unit conversions test\n";
}

void test_hazen_williams() {
    // 100 gpm in 2 inch pipe, C=120, 100 ft length
    double loss = hydraulics::HydraulicEngine::calculate_hazen_williams_loss_psi(100.0, 100.0, 120.0, 2.067);
    assert(loss > 0.0 && loss < 20.0);
    std::cout << "[PASS] Hazen-Williams calculation test (Loss: " << loss << " psi)\n";
}

void test_sprinkler_k_factor() {
    // K=5.6, P=10 psi -> Q = 5.6 * sqrt(10) = 17.708 GPM
    double flow = hydraulics::HydraulicEngine::calculate_sprinkler_flow_gpm(5.6, 10.0);
    assert(std::abs(flow - 17.708) < 0.1);
    std::cout << "[PASS] Sprinkler K-factor flow test (Flow: " << flow << " GPM)\n";
}

int main() {
    std::cout << "--- Running Hydraulic Engine Tests ---\n";
    test_unit_conversions();
    test_hazen_williams();
    test_sprinkler_k_factor();
    std::cout << "All hydraulic unit tests passed!\n";
    return 0;
}
