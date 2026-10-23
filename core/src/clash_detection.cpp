#include "fire_protection/clash_detection.hpp"

namespace fire_protection {
namespace clash {

std::vector<ClashResult> ClashEngine::detect_clashes(
    const std::vector<MepElement>& fire_elements,
    const std::vector<MepElement>& mep_elements,
    double clearance_tolerance_ft
) {
    std::vector<ClashResult> clashes;

    for (const auto& fire_elem : fire_elements) {
        for (const auto& mep_elem : mep_elements) {
            if (fire_elem.discipline == mep_elem.discipline) continue;

            if (fire_elem.bbox.intersects(mep_elem.bbox, clearance_tolerance_ft)) {
                bool hard_clash = fire_elem.bbox.intersects(mep_elem.bbox, 0.0);
                clashes.push_back({
                    fire_elem.id,
                    mep_elem.id,
                    mep_elem.discipline,
                    0.05, // Cubic ft interference
                    hard_clash
                });
            }
        }
    }

    return clashes;
}

} // namespace clash
} // namespace fire_protection
