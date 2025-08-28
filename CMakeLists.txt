cmake_minimum_required(VERSION 3.16)
project(EventManagerApp LANGUAGES CXX)

# -------------------------------
# C++ standard
# -------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# Include directories
# -------------------------------
include_directories(include)

# -------------------------------
# Library target
# -------------------------------
add_library(event_lib
    src/Event.cpp
    src/EventManager.cpp
)

target_include_directories(event_lib PUBLIC include)
target_compile_features(event_lib PUBLIC cxx_std_20)

# Compiler-specific warnings
if (MSVC)
    target_compile_options(event_lib PRIVATE /W4 /permissive-)
else()
    target_compile_options(event_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

# -------------------------------
# Main executable
# -------------------------------
add_executable(event_manager src/main.cpp)
target_link_libraries(event_manager PRIVATE event_lib)

# -------------------------------
# Optional tests
# -------------------------------
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
