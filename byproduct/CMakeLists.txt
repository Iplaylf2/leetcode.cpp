file(GLOB source-list *.cpp)
add_library(byproduct STATIC ${source-list})

target_include_directories(byproduct PUBLIC ${PROJECT_SOURCE_DIR}/include)