cmake_minimum_required(VERSION 3.20)
project(FireProtectionCore VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include)

add_compile_definitions(FIRE_PROTECTION_EXPORTS)

add_library(fire_protection_core SHARED
    src/hydraulics.cpp
    src/fire_alarm.cpp
    src/c_api.cpp
    src/clash_detection.cpp
)

enable_testing()

add_executable(test_hydraulics tests/test_hydraulics.cpp)
target_link_libraries(test_hydraulics PRIVATE fire_protection_core)
add_test(NAME TestHydraulics COMMAND test_hydraulics)

add_executable(test_fire_alarm tests/test_fire_alarm.cpp)
target_link_libraries(test_fire_alarm PRIVATE fire_protection_core)
add_test(NAME TestFireAlarm COMMAND test_fire_alarm)

add_executable(test_benchmarks tests/test_benchmarks.cpp)
target_link_libraries(test_benchmarks PRIVATE fire_protection_core)
add_test(NAME TestBenchmarks COMMAND test_benchmarks)

if(ENABLE_COVERAGE)
    target_compile_options(fire_protection_core PRIVATE --coverage -g -O0)
    target_link_options(fire_protection_core PRIVATE --coverage)
endif()

add_executable(test_clash_detection tests/test_clash_detection.cpp)
target_link_libraries(test_clash_detection PRIVATE fire_protection_core)
add_test(NAME TestClashDetection COMMAND test_clash_detection)
