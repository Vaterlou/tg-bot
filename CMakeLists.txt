cmake_minimum_required(VERSION 3.6)

project(pq-bot VERSION 0.1 LANGUAGES CXX)

enable_testing()

add_subdirectory(pq-bot)

set(BUILD_TESTS FALSE CACHE BOOL "Build unit tests")

if(BUILD_TESTS)
   message(STATUS "Building unit tests.")
   add_subdirectory(tests)
else()
   message(STATUS "Unit tests will not be built. To build unit tests, set BUILD_TESTS to true.")
endif()
