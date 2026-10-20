#include "fire_protection/c_api.h"
#ifndef FIRE_PROTECTION_HYDRAULICS_HPP
#define FIRE_PROTECTION_HYDRAULICS_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cmath>

namespace fire_protection {
namespace hydraulics {

enum class HeadLossFormula {
    HazenWilliams,
    DarcyWeisbach
};

struct Pipe {
    std::string id;
    std::string start_node_id;
    std::string end_node_id;
    double internal_diameter_inch; // Internal diameter in inches
    double length_feet;            // Pipe length in feet
    double c_factor;               // Hazen-Williams C factor (e.g. 120 for steel)
    double roughness_mm;           // Absolute roughness for Darcy-Weisbach in mm
    double fitting_equivalent_length_feet{0.0}; // Equivalent length of valves & fittings
};

struct Node {
    std::string id;
    double elevation_feet{0.0};
    double k_factor{0.0};          // Sprinkler K-factor (GPM/psi^0.5). 0 if normal junction.
    double minimum_pressure_psi{0.0}; // Minimum pressure required at this node
    double fixed_demand_gpm{0.0};  // Fixed outflow demand in GPM
    bool is_source{false};         // True if water supply source / pump node
    double source_static_pressure_psi{0.0};
    double source_residual_pressure_psi{0.0};
    double source_residual_flow_gpm{0.0};
};

struct PipeResult {
    std::string pipe_id;
    double flow_rate_gpm;          // Flow rate in GPM (signed for direction)
    double velocity_fps;           // Velocity in feet per second
    double friction_loss_psi;      // Friction loss in psi
    double total_head_loss_psi;    // Total loss (friction + elevation)
};

struct NodeResult {
    std::string node_id;
    double pressure_psi;           // Residual pressure at node in psi
    double total_demand_gpm;       // Outflow / discharge flow in GPM
};

struct CalculationResult {
    bool success{false};
    std::string error_message;
    int iterations_count{0};
    double total_system_flow_gpm{0.0};
    double total_system_demand_pressure_psi{0.0};
    double source_operating_pressure_psi{0.0};
    std::vector<PipeResult> pipe_results;
    std::vector<NodeResult> node_results;
};

class FP_API HydraulicEngine {
public:
    HydraulicEngine() = default;

    // Hazen-Williams friction head loss calculation per foot:
    // P_f (psi/ft) = 4.52 * Q^1.85 / (C^1.85 * d^4.87)
    static double calculate_hazen_williams_loss_psi(double flow_gpm, double length_ft, double c_factor, double diameter_inch);

    // Darcy-Weisbach friction head loss calculation in psi
    static double calculate_darcy_weisbach_loss_psi(double flow_gpm, double length_ft, double roughness_mm, double diameter_inch, double fluid_temp_c = 20.0);

    // Calculate flow through sprinkler orifice given pressure and K-factor: Q = K * sqrt(P)
    static double calculate_sprinkler_flow_gpm(double k_factor, double pressure_psi);

    // Solve tree pipe network
    CalculationResult solve_tree_network(
        const std::vector<Node>& nodes,
        const std::vector<Pipe>& pipes,
        HeadLossFormula formula = HeadLossFormula::HazenWilliams
    );

    // Solve looped/grid network using Hardy Cross method
    CalculationResult solve_grid_network_hardy_cross(
        const std::vector<Node>& nodes,
        const std::vector<Pipe>& pipes,
        HeadLossFormula formula = HeadLossFormula::HazenWilliams,
        int max_iterations = 200,
        double tolerance_gpm = 0.01
    );
};

} // namespace hydraulics
} // namespace fire_protection

#endif // FIRE_PROTECTION_HYDRAULICS_HPP
