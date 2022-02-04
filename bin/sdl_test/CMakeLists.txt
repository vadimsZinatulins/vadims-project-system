cmake_minimum_required(VERSION 3.10)

project(sdl_test VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
