#include "fire_protection/c_api.h"
#ifndef FIRE_PROTECTION_FIRE_ALARM_HPP
#define FIRE_PROTECTION_FIRE_ALARM_HPP

#include <string>
#include <vector>

namespace fire_protection {
namespace fire_alarm {

struct NotificationAppliance {
    std::string id;
    double current_draw_amperes;    // e.g., 0.12 A (120 mA) for strobe/horn
    double distance_from_source_feet;
};

struct NacCircuit {
    std::string id;
    double nominal_voltage_volts{24.0}; // Nominal DC voltage (e.g., 24V or 20.4V EOL limit)
    double wire_gauge_awg{14.0};        // e.g., 12 AWG, 14 AWG, 16 AWG, 18 AWG
    double wire_resistance_per_1000ft_ohms{3.07}; // Resistance for copper conductor
    std::vector<NotificationAppliance> appliances;
};

struct NacCircuitResult {
    std::string circuit_id;
    double total_current_amperes;
    double total_voltage_drop_volts;
    double end_of_line_voltage_volts;
    bool is_compliant;               // True if end voltage >= minimum allowable voltage (e.g. 20.4V)
    std::string warning_message;
};

struct BatteryCalculationInput {
    double standby_current_amperes;    // Total system standby current (A)
    double standby_hours{24.0};         // Standby duration per NFPA 72 (e.g., 24 or 60 hours)
    double alarm_current_amperes;      // Total system alarm current (A)
    double alarm_minutes{5.0};          // Alarm duration per NFPA 72 (e.g., 5 or 15 minutes)
    double safety_margin_factor{1.20};  // Safety factor (e.g., 20% safety margin = 1.20)
};

struct BatteryCalculationResult {
    double standby_amp_hours;
    double alarm_amp_hours;
    double total_required_amp_hours;
    double recommended_battery_capacity_ah; // Minimum recommended battery capacity in Ah
};

class FP_API FireAlarmEngine {
public:
    FireAlarmEngine() = default;

    // Helper to get copper wire resistance per 1000 ft at 75°C (NFPA 70 / Chapter 9 Table 8)
    static double get_wire_resistance_ohms_per_1000ft(int awg_size);

    // Calculate NAC circuit voltage drop (Class B / Class A 2-wire analysis)
    static NacCircuitResult calculate_nac_voltage_drop(
        const NacCircuit& circuit,
        double min_allowed_voltage_volts = 20.4
    );

    // Calculate secondary power supply battery capacity according to NFPA 72 Chapter 10
    static BatteryCalculationResult calculate_battery_capacity(
        const BatteryCalculationInput& input
    );
};

} // namespace fire_alarm
} // namespace fire_protection

#endif // FIRE_PROTECTION_FIRE_ALARM_HPP
