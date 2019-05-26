# Maestro Engine (maestro-engine)
cmake_minimum_required (VERSION 3.8)
project(maestro-engine)

# Get library source files.
file(GLOB maestro-engine-src
    "src/*.h"
    "src/*.cpp"
)

# Add library to project.
add_library(${PROJECT_NAME} ${maestro-engine-src})
add_library(mae::engine ALIAS ${PROJECT_NAME})

# Add include targets.
target_include_directories(${PROJECT_NAME} PUBLIC "./include")

# Add library targets.
set(SDL2_DIR ./)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
