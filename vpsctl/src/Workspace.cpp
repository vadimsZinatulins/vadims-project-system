#include "Workspace.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <streambuf>

void Workspace::create(std::string name, WSManager &wsManager)
{
	// If the current path already exists in the wsManager or the .vps exists
	// then the workspace was already initialized
	if(wsManager.find(std::filesystem::current_path()) != wsManager.end() || std::filesystem::exists(".vps"))
		return;

	auto ws = std::make_shared<Workspace>();

	ws->m_name = name;
	ws->m_majorVersion = 1;
	ws->m_minorVersion = 0;

	ws->createFile();

	wsManager[std::filesystem::current_path()] = ws;
}

Workspace::Workspace() {}
Workspace::Workspace(std::string path) {}
Workspace::~Workspace() {}

void Workspace::createFile() const
{
	std::ofstream configFile(".vps");
	configFile << m_name.size();
	configFile << m_name;
	configFile.close();
}

