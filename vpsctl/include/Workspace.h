#pragma once

#include "WSManager.h"

class Workspace final
{
public:
	Workspace();
	Workspace(std::string path);
	~Workspace();

	static void create(std::string name, WSManager &wsManager);

private:
	void updateCmakeFile() const;

	std::string m_name;
};
