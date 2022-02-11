#pragma once

#include <string>
#include <vector>

class Workspace final
{
public:
	Workspace();
	Workspace(std::string name);
	~Workspace();

	static Workspace create(std::string name);
private:
	void createFile() const;


	std::string m_name;

	int m_majorVersion;
	int m_minorVersion;

	std::vector<std::string> m_headerFiles;
	std::vector<std::string> m_cppFiles;
};
