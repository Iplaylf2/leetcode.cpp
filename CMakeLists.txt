cmake_minimum_required(VERSION 3.0.0)
project(leetcode VERSION 0.1.0)

add_subdirectory(launcher)
add_subdirectory(solution)
add_subdirectory(support)
add_subdirectory(byproduct)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
