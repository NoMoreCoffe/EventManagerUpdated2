cmake_minimum_required(VERSION 3.16)

# -------------------------------
# Use system-installed GoogleTest
# -------------------------------
find_package(GTest REQUIRED)

# -------------------------------
# Test executable
# -------------------------------
add_executable(run_tests
    test_event.cpp
    test_event_manager.cpp
    test_event_manager_errors.cpp
)

# Link test executable with your library and GTest
target_link_libraries(run_tests
    PRIVATE
    event_lib
    GTest::gtest_main
)

target_compile_features(run_tests PRIVATE cxx_std_20)

# Enable CTest and auto-discover tests
include(GoogleTest)
gtest_discover_tests(run_tests)
