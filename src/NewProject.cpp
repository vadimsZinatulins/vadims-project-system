#include "NewProject.h"

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

NewProject::NewProject(std::string name) : m_name(name) {}
NewProject::~NewProject() {}

void NewProject::create() const
{
	std::cout << "Creating new project called: " << m_name << std::endl;

	std::string path = createProjectStructure();
	createCMakeFile(path);

	std::ofstream mainFile(path + "/src/main.cpp");
	mainFile << "#include \"config.h\"\n\n";
	mainFile << "#include <iostream>\n\n";
	mainFile << "int main(int argc, char *argv[])\n{\n"; 
	mainFile << "\tstd::cout << \"Running Version: \" << MAJOR_VERSION << \".\" << MINOR_VERSION << std::endl;\n";
	mainFile << "\tstd::cout << \"Hello World!\" << std::endl;\n";
	mainFile << "\treturn 0;\n}\n";
	mainFile.close();

	std::ofstream configFile(path + "/config/config.h.in");
	configFile << "#pragma once\n\n";
	configFile << "#define MAJOR_VERSION @" << m_name << "_VERSION_MAJOR@\n";
	configFile << "#define MINOR_VERSION @" << m_name << "_VERSION_MINOR@\n";
	configFile.close();
}

std::string NewProject::createProjectStructure() const 
{
	fs::create_directory(m_name);

	fs::current_path(fs::current_path().string() + "/" + m_name);

	for(const auto &dir : { "bin", "build", "config", "include", "lib", "src" }) fs::create_directory(dir);

	return fs::current_path();
}

void NewProject::createCMakeFile(std::string path) const
{
	std::ofstream file(path + "/CMakeLists.txt");

	file << "cmake_minimum_required(VERSION 3.10)\n\n";
	file << "project(" << m_name << " VERSION 1.0)\n\n";
	file << "set(CMAKE_CXX_STANDARD 17)\n";
	file << "set(CMAKE_CXX_STANDARD_REQUIRED True)\n";
	file << "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n";
	file << "configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)\n\n";
	file << "add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)\n\n";
	file << "target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)\n\n";
	file << "set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)\n";

	file.close();
}

