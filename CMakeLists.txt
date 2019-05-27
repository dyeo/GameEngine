# Maestro Project (maestro)
cmake_minimum_required (VERSION 3.8)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DMAESTRO_DEBUG)
else()
	add_definitions(-DMAESTRO_RELEASE)
endif()

# Include project.
project(maestro)

# Include sub-projects.
add_subdirectory(maestro-engine)
add_subdirectory(maestro-tests)
