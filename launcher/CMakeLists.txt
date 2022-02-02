file(GLOB source-list *.cpp)
add_executable(launcher ${source-list})

target_link_libraries(launcher PRIVATE solution support)

target_include_directories(launcher PRIVATE ${PROJECT_SOURCE_DIR}/solution ${PROJECT_SOURCE_DIR}/support)