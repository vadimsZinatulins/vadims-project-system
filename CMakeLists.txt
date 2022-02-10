cmake_minimum_required(VERSION 3.10)

project(vadims-project-system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/utils/include)

add_subdirectory(vps)
add_subdirectory(vpsctl)
add_subdirectory(utils)

install(TARGETS vps vpsctl DESTINATION /usr/local/bin)
