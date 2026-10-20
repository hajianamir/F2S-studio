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

void test_battery_capacity() {
    BatteryCalculationInput input;
    input.standby_current_amperes = 0.200;
    input.standby_hours = 24.0;
    input.alarm_current_amperes = 1.000;
    input.alarm_minutes = 5.0;
    input.safety_margin_factor = 1.20;

    auto res = FireAlarmEngine::calculate_battery_capacity(input);
    // Standby: 0.2 * 24 = 4.8 Ah
    // Alarm: 1.0 * (5/60) = 0.0833 Ah
    // Total: 4.8833 * 1.20 = 5.86 Ah
    assert(std::abs(res.standby_amp_hours - 4.8) < 0.01);
    assert(res.recommended_battery_capacity_ah > 5.5);
    std::cout << "[PASS] Battery capacity test (Recommended: " << res.recommended_battery_capacity_ah << " Ah)\n";
}

int main() {
    std::cout << "--- Running Fire Alarm Engine Tests ---\n";
    test_nac_voltage_drop();
    test_battery_capacity();
    std::cout << "All fire alarm unit tests passed!\n";
    return 0;
}
