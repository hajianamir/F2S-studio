#include "fire_protection/seismic_bracing.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace fire_protection::seismic;

void test_seismic_bracing_nfpa13_worked_example() {
    SeismicZoneInput input;
    input.short_period_spectral_acceleration_sds = 1.0;
    input.component_importance_factor_ip = 1.5;
    input.total_pipe_weight_lbs = 1000.0;
    input.brace_angle_degrees = 45.0;

    auto res = SeismicEngine::calculate_sway_brace_load(input);
    assert(std::abs(res.seismic_coefficient_cp - 0.50) < 0.001);
    assert(std::abs(res.horizontal_seismic_force_f_pw - 500.0) < 0.1);
    assert(std::abs(res.required_brace_load_lbs - 707.1) < 1.0);
    assert(res.is_compliant == true);

    std::cout << "[PASS] NFPA 13 Ch. 18 Seismic Sway Bracing Worked Example Test (Load: " << res.required_brace_load_lbs << " lbs)\n";
}

int main() {
    std::cout << "--- Executing NFPA 13 Ch. 18 Seismic Bracing Tests ---\n";
    test_seismic_bracing_nfpa13_worked_example();
    std::cout << "All seismic bracing unit tests passed!\n";
    return 0;
}
