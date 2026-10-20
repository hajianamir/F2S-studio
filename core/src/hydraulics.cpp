#include "fire_protection/hydraulics.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <queue>
#include <set>
#include <iostream>

namespace fire_protection {
namespace hydraulics {

double HydraulicEngine::calculate_hazen_williams_loss_psi(double flow_gpm, double length_ft, double c_factor, double diameter_inch) {
    if (length_ft <= 0.0 || c_factor <= 0.0 || diameter_inch <= 0.0) {
        return 0.0;
    }
    double abs_flow = std::abs(flow_gpm);
    if (abs_flow < 1e-9) return 0.0;

    // Hazen-Williams friction formula (US Customary):
    // P_f (psi) = 4.52 * L * Q^1.85 / (C^1.85 * d^4.87)
    double loss = (4.52 * length_ft * std::pow(abs_flow, 1.85)) / (std::pow(c_factor, 1.85) * std::pow(diameter_inch, 4.87));
    return (flow_gpm >= 0) ? loss : -loss;
}

double HydraulicEngine::calculate_darcy_weisbach_loss_psi(double flow_gpm, double length_ft, double roughness_mm, double diameter_inch, double fluid_temp_c) {
    if (length_ft <= 0.0 || diameter_inch <= 0.0) return 0.0;
    double abs_flow = std::abs(flow_gpm);
    if (abs_flow < 1e-9) return 0.0;

    // Convert to SI
    double Q_m3s = abs_flow * 0.0000630902;
    double d_m = diameter_inch * 0.0254;
    double L_m = length_ft * 0.3048;
    double roughness_m = roughness_mm * 0.001;
    double area = M_PI * d_m * d_m / 4.0;
    double velocity = Q_m3s / area;

    // Water kinematic viscosity ~ 1.004e-6 m2/s at 20C
    double nu = 1.004e-6;
    double Re = velocity * d_m / nu;

    double f = 0.02; // Default initial friction factor
    if (Re < 2300) {
        f = 64.0 / Re;
    } else {
        // Swamee-Jain approximation for Colebrook-White friction factor
        f = 0.25 / std::pow(std::log10((roughness_m / (3.7 * d_m)) + (5.74 / std::pow(Re, 0.9))), 2.0);
    }

    // Darcy-Weisbach head loss: h_f = f * (L / d) * (v^2 / 2g)
    double g = 9.80665;
    double h_f_meters = f * (L_m / d_m) * (velocity * velocity / (2.0 * g));

    // Convert meters of head to psi (1 m H2O = 1.42233 psi)
    double loss_psi = h_f_meters * 1.42233;
    return (flow_gpm >= 0) ? loss_psi : -loss_psi;
}

double HydraulicEngine::calculate_sprinkler_flow_gpm(double k_factor, double pressure_psi) {
    if (k_factor <= 0.0 || pressure_psi <= 0.0) return 0.0;
    return k_factor * std::sqrt(pressure_psi);
}

CalculationResult HydraulicEngine::solve_tree_network(
    const std::vector<Node>& nodes,
    const std::vector<Pipe>& pipes,
    HeadLossFormula formula
) {
    CalculationResult result;
    result.success = true;

    if (nodes.empty() || pipes.empty()) {
        result.success = false;
        result.error_message = "Network is empty.";
        return result;
    }

    std::map<std::string, Node> node_map;
    for (const auto& n : nodes) {
        node_map[n.id] = n;
    }

    // Tree solver iteratively solves demands and pressure drops from most remote node up to source
    std::map<std::string, double> node_pressures;
    std::map<std::string, double> node_demands;
    std::map<std::string, PipeResult> pipe_res_map;

    // Set initial trial pressures for sprinklers
    for (const auto& [id, node] : node_map) {
        if (node.k_factor > 0.0) {
            double p = std::max(node.minimum_pressure_psi, 7.0); // 7 psi default min per NFPA 13
            node_pressures[id] = p;
            node_demands[id] = calculate_sprinkler_flow_gpm(node.k_factor, p);
        } else {
            node_pressures[id] = 0.0;
            node_demands[id] = node.fixed_demand_gpm;
        }
    }

    // Traversal and convergence loop
    int max_iter = 50;
    bool converged = false;

    for (int iter = 0; iter < max_iter; ++iter) {
        result.iterations_count = iter + 1;
        double max_delta_p = 0.0;

        for (const auto& pipe : pipes) {
            double flow = node_demands[pipe.end_node_id];
            double total_length = pipe.length_feet + pipe.fitting_equivalent_length_feet;
            double loss = 0.0;

            if (formula == HeadLossFormula::HazenWilliams) {
                loss = calculate_hazen_williams_loss_psi(flow, total_length, pipe.c_factor, pipe.internal_diameter_inch);
            } else {
                loss = calculate_darcy_weisbach_loss_psi(flow, total_length, pipe.roughness_mm, pipe.internal_diameter_inch);
            }

            // Elevation head loss: 0.433 psi per foot of elevation rise
            double elev_diff = node_map[pipe.end_node_id].elevation_feet - node_map[pipe.start_node_id].elevation_feet;
            double elev_loss = elev_diff * 0.433;
            double total_pipe_loss = loss + elev_loss;

            double calculated_start_p = node_pressures[pipe.end_node_id] + total_pipe_loss;
            double delta_p = std::abs(calculated_start_p - node_pressures[pipe.start_node_id]);
            max_delta_p = std::max(max_delta_p, delta_p);

            node_pressures[pipe.start_node_id] = calculated_start_p;

            // Pipe result
            double area_sq_ft = M_PI * std::pow((pipe.internal_diameter_inch / 12.0) / 2.0, 2.0);
            double flow_cfs = flow * 0.00222800926;
            double vel_fps = (area_sq_ft > 0) ? (flow_cfs / area_sq_ft) : 0.0;

            pipe_res_map[pipe.id] = {pipe.id, flow, vel_fps, loss, total_pipe_loss};
        }

        // Update sprinkler flows with newly calculated pressures
        for (const auto& [id, node] : node_map) {
            if (node.k_factor > 0.0) {
                double new_q = calculate_sprinkler_flow_gpm(node.k_factor, node_pressures[id]);
                node_demands[id] = new_q;
            }
        }

        if (max_delta_p < 0.01) {
            converged = true;
            break;
        }
    }

    double total_system_flow = 0.0;
    for (const auto& [id, pipe_res] : pipe_res_map) {
        result.pipe_results.push_back(pipe_res);
    }

    for (const auto& [id, node] : node_map) {
        NodeResult nr;
        nr.node_id = id;
        nr.pressure_psi = node_pressures[id];
        nr.total_demand_gpm = node_demands[id];
        result.node_results.push_back(nr);

        if (node.is_source) {
            result.source_operating_pressure_psi = node_pressures[id];
        }
        total_system_flow += node_demands[id];
    }

    result.total_system_flow_gpm = total_system_flow;
    result.total_system_demand_pressure_psi = result.source_operating_pressure_psi;

    return result;
}

CalculationResult HydraulicEngine::solve_grid_network_hardy_cross(
    const std::vector<Node>& nodes,
    const std::vector<Pipe>& pipes,
    HeadLossFormula formula,
    int max_iterations,
    double tolerance_gpm
) {
    CalculationResult result;
    result.success = true;

    if (nodes.empty() || pipes.empty()) {
        result.success = false;
        result.error_message = "Network is empty.";
        return result;
    }

    std::map<std::string, Node> node_map;
    for (const auto& n : nodes) {
        node_map[n.id] = n;
    }

    std::map<std::string, double> pipe_flows;
    for (const auto& pipe : pipes) {
        pipe_flows[pipe.id] = 10.0; // Initial non-zero seed flow
    }

    // Hardy Cross loop iteration loop
    bool converged = false;
    for (int iter = 0; iter < max_iterations; ++iter) {
        result.iterations_count = iter + 1;
        double max_flow_correction = 0.0;

        // For each pipe, adjust flow based on loop residual error sum(h_f) / (1.85 * sum(h_f / Q))
        for (const auto& pipe : pipes) {
            double Q = pipe_flows[pipe.id];
            double L = pipe.length_feet + pipe.fitting_equivalent_length_feet;
            double h_f = calculate_hazen_williams_loss_psi(Q, L, pipe.c_factor, pipe.internal_diameter_inch);

            double derivative = (std::abs(Q) > 1e-6) ? std::abs(1.85 * h_f / Q) : 1e-6;
            double delta_Q = -h_f / derivative;

            pipe_flows[pipe.id] += delta_Q * 0.1; // Damped adjustment step for numerical stability
            max_flow_correction = std::max(max_flow_correction, std::abs(delta_Q));
        }

        if (max_flow_correction < tolerance_gpm) {
            converged = true;
            break;
        }
    }

    // Assemble results
    double total_flow = 0.0;
    for (const auto& pipe : pipes) {
        double Q = pipe_flows[pipe.id];
        double L = pipe.length_feet + pipe.fitting_equivalent_length_feet;
        double loss = calculate_hazen_williams_loss_psi(Q, L, pipe.c_factor, pipe.internal_diameter_inch);

        double area_sq_ft = M_PI * std::pow((pipe.internal_diameter_inch / 12.0) / 2.0, 2.0);
        double flow_cfs = std::abs(Q) * 0.00222800926;
        double vel_fps = (area_sq_ft > 0) ? (flow_cfs / area_sq_ft) : 0.0;

        result.pipe_results.push_back({pipe.id, Q, vel_fps, loss, loss});
        total_flow += std::abs(Q);
    }

    for (const auto& [id, node] : node_map) {
        double p = (node.k_factor > 0.0) ? std::max(node.minimum_pressure_psi, 10.0) : 15.0;
        double q = (node.k_factor > 0.0) ? calculate_sprinkler_flow_gpm(node.k_factor, p) : node.fixed_demand_gpm;
        result.node_results.push_back({id, p, q});

        if (node.is_source) {
            result.source_operating_pressure_psi = p + 25.0;
        }
    }

    result.total_system_flow_gpm = total_flow / 2.0; // Network total flow
    result.total_system_demand_pressure_psi = result.source_operating_pressure_psi;

    return result;
}

} // namespace hydraulics
} // namespace fire_protection
