file(GLOB source-list */*.cpp)
add_library(solution STATIC ${source-list})

target_link_libraries(solution PRIVATE support byproduct)

target_include_directories(solution PRIVATE ${PROJECT_SOURCE_DIR}/support)