#ifndef FIRE_PROTECTION_SEISMIC_BRACING_HPP
#define FIRE_PROTECTION_SEISMIC_BRACING_HPP

#include "fire_protection/c_api.h"
#include <string>
#include <vector>

namespace fire_protection {
namespace seismic {

struct SeismicZoneInput {
    double short_period_spectral_acceleration_sds{1.0}; // S_ds per NFPA 13 Chapter 18
    double component_importance_factor_ip{1.5};         // I_p = 1.5 for fire systems per NFPA 13
    double total_pipe_weight_lbs{1200.0};              // Total water-filled pipe weight in zone of influence
    double brace_angle_degrees{45.0};                   // Brace installation angle from vertical (30 to 90 deg)
};

struct SeismicBraceResult {
    double seismic_coefficient_cp;      // C_p = 0.4 * S_ds * I_p
    double horizontal_seismic_force_f_pw; // F_pw = C_p * W_p
    double required_brace_load_lbs;     // Design load along brace axis = F_pw / sin(angle)
    bool is_compliant;
    std::string recommended_brace_type;
};

class FP_API SeismicEngine {
public:
    // Calculate NFPA 13 Chapter 18 Zone of Influence seismic sway bracing load
    static SeismicBraceResult calculate_sway_brace_load(const SeismicZoneInput& input);
};

} // namespace seismic
} // namespace fire_protection

#endif // FIRE_PROTECTION_SEISMIC_BRACING_HPP
