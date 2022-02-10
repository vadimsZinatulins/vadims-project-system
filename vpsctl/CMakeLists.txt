project(vpsctl VERSION 0.1)

configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} utils)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
