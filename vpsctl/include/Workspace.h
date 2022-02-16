#pragma once

#include "WSManager.h"

class Workspace final
{
public:
	static void create(std::string name, WSManager &wsManager);

	std::string getName() const;
private:
	void updateCmakeFile() const;

	std::string m_name;
};
