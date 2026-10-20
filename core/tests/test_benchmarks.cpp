#include "fire_protection/hydraulics.hpp"
#include "fire_protection/fire_alarm.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace fire_protection;

void test_bench01_tree() {
    hydraulics::HydraulicEngine engine;
    std::vector<hydraulics::Node> nodes = {
        {"SRC", 0.0, 0.0, 0.0, 0.0, true, 50.0, 30.0, 500.0},
        {"N1", 10.0, 5.6, 7.0, 0.0, false, 0.0, 0.0, 0.0},
        {"N2", 10.0, 5.6, 7.0, 0.0, false, 0.0, 0.0, 0.0},
        {"N3", 10.0, 5.6, 7.0, 0.0, false, 0.0, 0.0, 0.0}
    };
    std::vector<hydraulics::Pipe> pipes = {
        {"P_SRC", "SRC", "N1", 2.067, 50.0, 120.0, 0.0, 0.0},
        {"P12", "N1", "N2", 1.380, 12.0, 120.0, 0.0, 0.0},
        {"P23", "N2", "N3", 1.049, 12.0, 120.0, 0.0, 0.0}
    };

    auto res = engine.solve_tree_network(nodes, pipes);
    assert(res.success);
    assert(res.total_system_flow_gpm > 0.0);
    std::cout << "[BENCHMARK PASS] Bench 01 NFPA 13 Tree System (Total Flow: " << res.total_system_flow_gpm << " GPM)\n";
}

void test_bench02_grid() {
    hydraulics::HydraulicEngine engine;
    std::vector<hydraulics::Node> nodes = {
        {"SRC", 0.0, 0.0, 0.0, 0.0, true},
        {"G1", 12.0, 5.6, 10.0, 0.0},
        {"G2", 12.0, 5.6, 10.0, 0.0},
        {"G3", 12.0, 5.6, 10.0, 0.0},
        {"G4", 12.0, 5.6, 10.0, 0.0}
    };
    std::vector<hydraulics::Pipe> pipes = {
        {"P_FEED", "SRC", "G1", 2.5, 40.0, 120.0, 0.0, 0.0},
        {"P12", "G1", "G2", 1.5, 20.0, 120.0, 0.0, 0.0},
        {"P24", "G2", "G4", 1.5, 20.0, 120.0, 0.0, 0.0},
        {"P43", "G4", "G3", 1.5, 20.0, 120.0, 0.0, 0.0},
        {"P31", "G3", "G1", 1.5, 20.0, 120.0, 0.0, 0.0}
    };

    auto res = engine.solve_grid_network_hardy_cross(nodes, pipes);
    assert(res.success);
    assert(res.pipe_results.size() == 5);
    std::cout << "[BENCHMARK PASS] Bench 02 2x2 Looped Grid System (Hardy Cross iterations: " << res.iterations_count << ")\n";
}

void test_bench04_nac() {
    fire_alarm::NacCircuit circuit;
    circuit.id = "BENCH_NAC";
    circuit.nominal_voltage_volts = 24.0;
    circuit.wire_gauge_awg = 14;
    circuit.wire_resistance_per_1000ft_ohms = 3.07;

    for (int i = 1; i <= 10; ++i) {
        circuit.appliances.push_back({"S" + std::to_string(i), 0.12, i * 25.0});
    }

    auto res = fire_alarm::FireAlarmEngine::calculate_nac_voltage_drop(circuit);
    assert(std::abs(res.total_current_amperes - 1.20) < 0.001);
    assert(res.end_of_line_voltage_volts > 20.0);
    std::cout << "[BENCHMARK PASS] Bench 04 NAC Circuit (Total Current: " << res.total_current_amperes << " A, EOL V: " << res.end_of_line_voltage_volts << " V)\n";
}

int main() {
    std::cout << "--- Executing Benchmark Golden Tests ---\n";
    test_bench01_tree();
    test_bench02_grid();
    test_bench04_nac();
    std::cout << "All Benchmark Golden Tests Executed Successfully!\n";
    return 0;
}
