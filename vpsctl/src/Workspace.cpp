#include "Workspace.h"

#include <fstream>
#include <filesystem>
#include <memory>

void Workspace::create(std::string name, WSManager &wsManager)
{
	// Create directory with workspace name
	std::filesystem::create_directory(name);
	// Change directory to newly created directory
	std::filesystem::current_path(std::filesystem::current_path().string() + "/" + name);

	auto ws = std::make_shared<Workspace>();

	ws->m_name = name;

	// Create cmake file
	ws->updateCmakeFile();

	// Store workspace in memory
	wsManager[std::filesystem::current_path()] = ws;
}

Workspace::Workspace() {}
Workspace::Workspace(std::string path) {}
Workspace::~Workspace() {}

void Workspace::updateCmakeFile() const
{
	std::ofstream cmakeFile("CMakeLists.txt", std::ios::trunc);

	cmakeFile << "cmake_minimum_required(VERSION 3.10)\n\n";
	cmakeFile << "project(" << m_name << ")\n\n";

	cmakeFile.close();
}

