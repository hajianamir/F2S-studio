#include "fire_protection/fire_alarm.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace fire_protection::fire_alarm;

void test_nac_voltage_drop() {
    NacCircuit circuit;
    circuit.id = "NAC_MAIN";
    circuit.nominal_voltage_volts = 24.0;
    circuit.wire_gauge_awg = 14;
    circuit.wire_resistance_per_1000ft_ohms = 3.07;
    circuit.appliances = {
        {"A1", 0.15, 100.0},
        {"A2", 0.15, 200.0}
    };

    auto res = FireAlarmEngine::calculate_nac_voltage_drop(circuit);
    assert(res.total_current_amperes == 0.30);
    assert(res.end_of_line_voltage_volts > 20.4);
    assert(res.is_compliant == true);
    std::cout << "[PASS] NAC circuit voltage drop test (EOL V: " << res.end_of_line_voltage_volts << " V)\n";
}

void test_nac_voltage_drop_failing() {
    NacCircuit circuit;
    circuit.id = "NAC_FAIL";
    circuit.nominal_voltage_volts = 24.0;
    circuit.wire_gauge_awg = 18; // Higher resistance 7.95 ohms/1000ft
    circuit.wire_resistance_per_1000ft_ohms = 7.95;
    circuit.appliances = {
        {"A1", 1.50, 500.0},
        {"A2", 1.50, 1000.0}
    };

    auto res = FireAlarmEngine::calculate_nac_voltage_drop(circuit, 20.4);
    assert(!res.is_compliant);
    assert(!res.warning_message.empty());
    std::cout << "[PASS] NAC non-compliant voltage drop test (Warning: " << res.warning_message << ")\n";
}

void test_nac_empty_appliances() {
    NacCircuit circuit;
    circuit.id = "NAC_EMPTY";
    circuit.nominal_voltage_volts = 24.0;
    auto res = FireAlarmEngine::calculate_nac_voltage_drop(circuit);
    assert(res.end_of_line_voltage_volts == 24.0);
    std::cout << "[PASS] Empty NAC appliances branch test\n";
}

void test_wire_gauge_branches() {
    assert(FireAlarmEngine::get_wire_resistance_ohms_per_1000ft(12) == 1.93);
    assert(FireAlarmEngine::get_wire_resistance_ohms_per_1000ft(14) == 3.07);
    assert(FireAlarmEngine::get_wire_resistance_ohms_per_1000ft(16) == 4.99);
    assert(FireAlarmEngine::get_wire_resistance_ohms_per_1000ft(18) == 7.95);
    assert(FireAlarmEngine::get_wire_resistance_ohms_per_1000ft(10) == 3.07); // Default branch
    std::cout << "[PASS] Wire gauge AWG branch lookup test\n";
}

void test_battery_capacity() {
    BatteryCalculationInput input;
    input.standby_current_amperes = 0.200;
    input.standby_hours = 24.0;
    input.alarm_current_amperes = 1.000;
    input.alarm_minutes = 5.0;
    input.safety_margin_factor = 1.20;

    auto res = FireAlarmEngine::calculate_battery_capacity(input);
    assert(std::abs(res.standby_amp_hours - 4.8) < 0.01);
    assert(res.recommended_battery_capacity_ah > 5.5);
    std::cout << "[PASS] Battery capacity test (Recommended: " << res.recommended_battery_capacity_ah << " Ah)\n";
}

int main() {
    std::cout << "--- Running Enhanced Fire Alarm Engine Tests ---\n";
    test_nac_voltage_drop();
    test_nac_voltage_drop_failing();
    test_nac_empty_appliances();
    test_wire_gauge_branches();
    test_battery_capacity();
    std::cout << "All fire alarm unit tests passed!\n";
    return 0;
}
