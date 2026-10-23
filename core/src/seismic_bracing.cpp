#include "fire_protection/seismic_bracing.hpp"
#include <cmath>
#include <algorithm>

namespace fire_protection {
namespace seismic {

SeismicBraceResult SeismicEngine::calculate_sway_brace_load(const SeismicZoneInput& input) {
    SeismicBraceResult res;

    // C_p = 0.4 * S_ds * I_p (NFPA 13 Section 18.5.9.3)
    res.seismic_coefficient_cp = std::min(0.4 * input.short_period_spectral_acceleration_sds * input.component_importance_factor_ip, 0.50);

    // F_pw = C_p * W_p
    res.horizontal_seismic_force_f_pw = res.seismic_coefficient_cp * input.total_pipe_weight_lbs;

    // Convert brace angle to radians (angle measured from vertical)
    double angle_rad = input.brace_angle_degrees * (M_PI / 180.0);
    double sin_angle = std::sin(angle_rad);
    if (sin_angle <= 0.0) sin_angle = 0.7071; // Fallback to 45 deg

    res.required_brace_load_lbs = res.horizontal_seismic_force_f_pw / sin_angle;
    res.is_compliant = true;

    if (res.required_brace_load_lbs <= 1500.0) {
        res.recommended_brace_type = "Light-Duty Rigid Angle Brace (1.5 in x 1.5 in x 3/16 in)";
    } else {
        res.recommended_brace_type = "Heavy-Duty Schedule 40 Steel Pipe Sway Brace (2.0 in)";
    }

    return res;
}

} // namespace seismic
} // namespace fire_protection
