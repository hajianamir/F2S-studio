#include "fire_protection/fire_alarm.hpp"
#include <algorithm>
#include <sstream>

namespace fire_protection {
namespace fire_alarm {

double FireAlarmEngine::get_wire_resistance_ohms_per_1000ft(int awg_size) {
    switch (awg_size) {
        case 12: return 1.93;  // 12 AWG solid uncoated copper @ 75°C
        case 14: return 3.07;  // 14 AWG
        case 16: return 4.99;  // 16 AWG
        case 18: return 7.95;  // 18 AWG
        default: return 3.07;
    }
}

NacCircuitResult FireAlarmEngine::calculate_nac_voltage_drop(
    const NacCircuit& circuit,
    double min_allowed_voltage_volts
) {
    NacCircuitResult result;
    result.circuit_id = circuit.id;
    result.total_current_amperes = 0.0;
    result.total_voltage_drop_volts = 0.0;
    result.is_compliant = true;

    if (circuit.appliances.empty()) {
        result.end_of_line_voltage_volts = circuit.nominal_voltage_volts;
        return result;
    }

    // Calculate total current draw
    for (const auto& app : circuit.appliances) {
        result.total_current_amperes += app.current_draw_amperes;
    }

    // Point-by-point voltage drop calculation along 2-wire conductor (2x distance for feed + return)
    double r_per_ft = circuit.wire_resistance_per_1000ft_ohms / 1000.0;
    double current_remaining = result.total_current_amperes;
    double prev_distance = 0.0;
    double accumulated_drop = 0.0;

    for (const auto& app : circuit.appliances) {
        double segment_distance = app.distance_from_source_feet - prev_distance;
        if (segment_distance > 0.0) {
            // 2 conductors (go and return)
            double segment_resistance = 2.0 * segment_distance * r_per_ft;
            accumulated_drop += current_remaining * segment_resistance;
        }
        current_remaining -= app.current_draw_amperes;
        prev_distance = app.distance_from_source_feet;
    }

    result.total_voltage_drop_volts = accumulated_drop;
    result.end_of_line_voltage_volts = circuit.nominal_voltage_volts - result.total_voltage_drop_volts;

    if (result.end_of_line_voltage_volts < min_allowed_voltage_volts) {
        result.is_compliant = false;
        std::ostringstream ss;
        ss << "End-of-line voltage (" << result.end_of_line_voltage_volts
           << " V) is below minimum required voltage (" << min_allowed_voltage_volts << " V).";
        result.warning_message = ss.str();
    }

    return result;
}

BatteryCalculationResult FireAlarmEngine::calculate_battery_capacity(
    const BatteryCalculationInput& input
) {
    BatteryCalculationResult result;
    result.standby_amp_hours = input.standby_current_amperes * input.standby_hours;
    result.alarm_amp_hours = input.alarm_current_amperes * (input.alarm_minutes / 60.0);

    double raw_total = result.standby_amp_hours + result.alarm_amp_hours;
    result.total_required_amp_hours = raw_total;
    result.recommended_battery_capacity_ah = raw_total * std::max(input.safety_margin_factor, 1.25);

    return result;
}

} // namespace fire_alarm
} // namespace fire_protection
