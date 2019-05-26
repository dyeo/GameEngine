# Maestro Tests (maestro-tests)
cmake_minimum_required (VERSION 3.8)
project(maestro-tests)

# Get library source files.
file(GLOB maestro-tests-src
    "src/*.h"
    "src/*.cpp"
)

# Add executable to project
add_executable(${PROJECT_NAME} ${maestro-tests-src})

# Add include targets.
target_include_directories(${PROJECT_NAME} PUBLIC "../maestro-engine/src")

# Add library targets.
target_link_libraries(${PROJECT_NAME} mae::engine)