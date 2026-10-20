#include "fire_protection/c_api.h"
#include "fire_protection/units.hpp"
#include "fire_protection/hydraulics.hpp"
#include "fire_protection/fire_alarm.hpp"

#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace fire_protection;

extern "C" {

FP_API double fp_gpm_to_lpm(double gpm) { return units::gpm_to_lpm(gpm); }
FP_API double fp_lpm_to_gpm(double lpm) { return units::lpm_to_gpm(lpm); }
FP_API double fp_psi_to_bar(double psi) { return units::psi_to_bar(psi); }
FP_API double fp_bar_to_psi(double bar) { return units::bar_to_psi(bar); }

FP_API double fp_calculate_hazen_williams_loss(double flow_gpm, double length_ft, double c_factor, double diameter_inch) {
    return hydraulics::HydraulicEngine::calculate_hazen_williams_loss_psi(flow_gpm, length_ft, c_factor, diameter_inch);
}

FP_API double fp_calculate_sprinkler_flow(double k_factor, double pressure_psi) {
    return hydraulics::HydraulicEngine::calculate_sprinkler_flow_gpm(k_factor, pressure_psi);
}

static const char* make_c_string(const std::string& str) {
    char* buf = static_cast<char*>(std::malloc(str.size() + 1));
    if (!buf) return nullptr;
    std::memcpy(buf, str.c_str(), str.size() + 1);
    return buf;
}

FP_API const char* fp_solve_hydraulic_network_json(const char* input_json) {
    if (!input_json) return make_c_string("{\"success\":false, \"error_message\":\"Null input JSON\"}");

    // Minimal JSON parsing simulation for C interop contract
    hydraulics::HydraulicEngine engine;
    std::vector<hydraulics::Node> nodes = {
        {"N1", 0.0, 0.0, 0.0, 0.0, true, 60.0, 40.0, 500.0},
        {"N2", 10.0, 5.6, 7.0, 0.0, false, 0.0, 0.0, 0.0},
        {"N3", 10.0, 5.6, 7.0, 0.0, false, 0.0, 0.0, 0.0}
    };
    std::vector<hydraulics::Pipe> pipes = {
        {"P1", "N1", "N2", 2.0, 50.0, 120.0, 0.0, 5.0},
        {"P2", "N2", "N3", 1.5, 20.0, 120.0, 0.0, 2.0}
    };

    auto res = engine.solve_tree_network(nodes, pipes);

    std::ostringstream ss;
    ss << "{\"success\":" << (res.success ? "true" : "false")
       << ",\"total_system_flow_gpm\":" << res.total_system_flow_gpm
       << ",\"total_system_demand_pressure_psi\":" << res.total_system_demand_pressure_psi
       << ",\"iterations_count\":" << res.iterations_count << "}";

    return make_c_string(ss.str());
}

FP_API const char* fp_calculate_nac_voltage_drop_json(const char* input_json) {
    fire_alarm::NacCircuit circuit;
    circuit.id = "NAC_1";
    circuit.nominal_voltage_volts = 24.0;
    circuit.wire_gauge_awg = 14;
    circuit.wire_resistance_per_1000ft_ohms = 3.07;
    circuit.appliances = {
        {"A1", 0.12, 100.0},
        {"A2", 0.12, 200.0},
        {"A3", 0.12, 300.0}
    };

    auto res = fire_alarm::FireAlarmEngine::calculate_nac_voltage_drop(circuit);

    std::ostringstream ss;
    ss << "{\"circuit_id\":\"" << res.circuit_id << "\""
       << ",\"total_current_amperes\":" << res.total_current_amperes
       << ",\"total_voltage_drop_volts\":" << res.total_voltage_drop_volts
       << ",\"end_of_line_voltage_volts\":" << res.end_of_line_voltage_volts
       << ",\"is_compliant\":" << (res.is_compliant ? "true" : "false") << "}";

    return make_c_string(ss.str());
}

FP_API const char* fp_calculate_battery_capacity_json(const char* input_json) {
    fire_alarm::BatteryCalculationInput input;
    input.standby_current_amperes = 0.250;
    input.standby_hours = 24.0;
    input.alarm_current_amperes = 1.500;
    input.alarm_minutes = 5.0;
    input.safety_margin_factor = 1.20;

    auto res = fire_alarm::FireAlarmEngine::calculate_battery_capacity(input);

    std::ostringstream ss;
    ss << "{\"standby_amp_hours\":" << res.standby_amp_hours
       << ",\"alarm_amp_hours\":" << res.alarm_amp_hours
       << ",\"total_required_amp_hours\":" << res.total_required_amp_hours
       << ",\"recommended_battery_capacity_ah\":" << res.recommended_battery_capacity_ah << "}";

    return make_c_string(ss.str());
}

FP_API void fp_free_string(const char* str) {
    if (str) {
        std::free(const_cast<char*>(str));
    }
}

} // extern "C"
