#include "fire_protection/clash_detection.hpp"
#include <iostream>
#include <cassert>

using namespace fire_protection::clash;

void test_clash_detection() {
    MepElement pipe = {"P101", "FIRE", {0, 0, 0, 10, 1, 1}};
    MepElement duct = {"D201", "HVAC", {5, 0.5, 0.5, 15, 3, 3}};
    MepElement beam = {"B301", "STRUCTURAL", {20, 0, 0, 30, 2, 2}};

    auto clashes = ClashEngine::detect_clashes({pipe}, {duct, beam});
    assert(clashes.size() == 1);
    assert(clashes[0].fire_element_id == "P101");
    assert(clashes[0].mep_element_id == "D201");
    assert(clashes[0].is_hard_clash == true);
    std::cout << "[PASS] MEP Spatial Hard Clash Detection Test\n";
}

int main() {
    std::cout << "--- Executing MEP Clash Detection Tests ---\n";
    test_clash_detection();
    std::cout << "All MEP clash detection unit tests passed!\n";
    return 0;
}
