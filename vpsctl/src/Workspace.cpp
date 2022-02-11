#include "Workspace.h"

void createWorkspaceFile()
{

}

Workspace Workspace::create(std::string name)
{
	Workspace ws;
	ws.m_name = name;
	ws.m_majorVersion = 1;
	ws.m_minorVersion = 0;

	return ws;
}

Workspace::Workspace() {}
Workspace::Workspace(std::string path) {}
Workspace::~Workspace() {}

