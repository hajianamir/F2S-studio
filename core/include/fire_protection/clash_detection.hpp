#ifndef FIRE_PROTECTION_CLASH_DETECTION_HPP
#define FIRE_PROTECTION_CLASH_DETECTION_HPP

#include "fire_protection/c_api.h"
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

namespace fire_protection {
namespace clash {

struct BoundingBox {
    double min_x, min_y, min_z;
    double max_x, max_y, max_z;

    bool intersects(const BoundingBox& other, double tolerance_ft = 0.0) const {
        return (min_x - tolerance_ft <= other.max_x) && (max_x + tolerance_ft >= other.min_x) &&
               (min_y - tolerance_ft <= other.max_y) && (max_y + tolerance_ft >= other.min_y) &&
               (min_z - tolerance_ft <= other.max_z) && (max_z + tolerance_ft >= other.min_z);
    }
};

struct MepElement {
    std::string id;
    std::string discipline; // "HVAC", "STRUCTURAL", "ELECTRICAL", "FIRE"
    BoundingBox bbox;
};

struct ClashResult {
    std::string fire_element_id;
    std::string mep_element_id;
    std::string mep_discipline;
    double interference_volume_cuft;
    bool is_hard_clash;
};

struct BvhNode {
    BoundingBox box;
    int left_child{-1};
    int right_child{-1};
    int element_index{-1};
    bool is_leaf() const { return left_child == -1 && right_child == -1; }
};

class FP_API ClashEngine {
public:
    static std::vector<ClashResult> detect_clashes(
        const std::vector<MepElement>& fire_elements,
        const std::vector<MepElement>& mep_elements,
        double clearance_tolerance_ft = 0.1
    );
};

} // namespace clash
} // namespace fire_protection

#endif // FIRE_PROTECTION_CLASH_DETECTION_HPP
