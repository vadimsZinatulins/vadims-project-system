#pragma once

#include <string>

class NewProject final
{
public:
	NewProject(std::string name);
	~NewProject();

	void create() const;
private:
	std::string createProjectStructure() const;
	void createCMakeFile(std::string path) const;

	std::string m_name;
};
