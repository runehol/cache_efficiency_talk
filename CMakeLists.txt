
# Preamble
cmake_minimum_required (VERSION 3.13)
project (cache_efficiency_talk LANGUAGES CXX C)
# The version number.
set (cache_efficiency_talk_VERSION_MAJOR 1)
set (cache_efficiency_talk_VERSION_MINOR 0)


# Project wide setup

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)



# Main targets built by this project

add_subdirectory(dependencies)


add_executable(benchmark_cache_efficiency_talk)

target_sources(benchmark_cache_efficiency_talk PRIVATE
	transpose_simple.cpp
	transpose_blocked.cpp
	benchmark.cpp
	)

target_link_libraries(benchmark_cache_efficiency_talk PRIVATE benchmark::benchmark)

add_custom_target(run_benchmark
COMMAND benchmark_cache_efficiency_talk
DEPENDS benchmark_cache_efficiency_talk
USES_TERMINAL
)
