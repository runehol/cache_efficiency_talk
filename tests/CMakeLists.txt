include( CTest )

include(GoogleTest)

add_executable(test_cache_efficiency_talk)

target_sources(test_cache_efficiency_talk PRIVATE
	test_transpose.cpp
	)

target_link_libraries(test_cache_efficiency_talk PRIVATE gtest_main)
target_link_libraries(test_cache_efficiency_talk PRIVATE cache_efficiency_talk)


gtest_discover_tests(test_cache_efficiency_talk WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")

set(CMAKE_CTEST_COMMAND ctest --progress --output-on-failure)

add_custom_target(check
COMMAND ${CMAKE_CTEST_COMMAND}
DEPENDS test_cache_efficiency_talk
USES_TERMINAL
)
