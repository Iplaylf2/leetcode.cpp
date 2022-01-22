add_executable(launcher launcher.cpp)

target_link_libraries(launcher PRIVATE solution support byproduct)

target_include_directories(launcher PRIVATE ${PROJECT_SOURCE_DIR}/solution ${PROJECT_SOURCE_DIR}/support)