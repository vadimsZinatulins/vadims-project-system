#include "Workspace.h"

#include <iostream>
#include <fstream>
#include <filesystem>

Workspace Workspace::create(std::string name)
{
	std::cout << "Creating Workspace called " << name << std::endl;

	Workspace ws;
	ws.m_name = name;
	ws.m_majorVersion = 1;
	ws.m_minorVersion = 0;

	ws.createFile();

	return ws;
}

Workspace::Workspace() {}
Workspace::Workspace(std::string path) {}
Workspace::~Workspace() {}

void Workspace::createFile() const
{
	std::cout << "Create .vps file" << std::endl;
	
	std::ofstream configFile(".vps");
	configFile << m_name.size();
	configFile << m_name;
	configFile.close();
}

