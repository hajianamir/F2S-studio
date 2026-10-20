#ifndef FIRE_PROTECTION_C_API_H
#define FIRE_PROTECTION_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
  #ifdef FIRE_PROTECTION_EXPORTS
    #define FP_API __declspec(dllexport)
  #else
    #define FP_API __declspec(dllimport)
  #endif
#else
  #define FP_API __attribute__((visibility("default")))
#endif

// Unit conversion C API
FP_API double fp_gpm_to_lpm(double gpm);
FP_API double fp_lpm_to_gpm(double lpm);
FP_API double fp_psi_to_bar(double psi);
FP_API double fp_bar_to_psi(double bar);

// Hydraulic computation C API
FP_API double fp_calculate_hazen_williams_loss(double flow_gpm, double length_ft, double c_factor, double diameter_inch);
FP_API double fp_calculate_sprinkler_flow(double k_factor, double pressure_psi);

// JSON-based pipeline execution for backend interop
// Takes JSON input representation of network/circuit, executes calculation, and returns JSON string result.
// Output memory buffer is allocated by C++ core and must be freed using fp_free_string.
FP_API const char* fp_solve_hydraulic_network_json(const char* input_json);
FP_API const char* fp_calculate_nac_voltage_drop_json(const char* input_json);
FP_API const char* fp_calculate_battery_capacity_json(const char* input_json);

FP_API void fp_free_string(const char* str);

#ifdef __cplusplus
}
#endif

#endif // FIRE_PROTECTION_C_API_H
