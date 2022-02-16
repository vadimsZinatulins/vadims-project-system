project(utils)

configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

add_library(${PROJECT_NAME} src/ArgProc.cpp src/Arguments.cpp src/Daemon.cpp src/NamedPipe.cpp src/NewProject.cpp src/PidFile.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
