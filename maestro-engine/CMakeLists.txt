# Maestro Engine (maestro-engine)
cmake_minimum_required (VERSION 3.8)

# Get library source files.
file(GLOB maestro_SRC
    "src/*.h"
    "src/*.cpp"
)

# Add library to project.
add_library(maestro ${maestro_SRC})

# Add include targets.
target_include_directories(maestro PUBLIC include)

# Add library targets.
set(SDL2_DIR modules)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(maestro STATIC ${SDL2_LIBRARIES})
