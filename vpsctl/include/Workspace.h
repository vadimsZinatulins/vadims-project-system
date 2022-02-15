#pragma once

#include "WSManager.h"

#include <string>
#include <vector>

class Workspace final
{
public:
	Workspace();
	Workspace(std::string name);
	~Workspace();

	static void create(std::string name, WSManager &wsManager);

	void setMajorVersion(unsigned int version);
	void setMinorVersion(unsigned int version);

	unsigned int getMajorVerion() const;
	unsigned int getMinorVersion() const;
private:
	struct Buffer
	{
		char *data;
		std::size_t size;
	};

	void updateCmakeFile() const;
	void createFile() const;

	Buffer serialize() const;
	void deserialize(Buffer buffer);

	std::string m_name;

	char m_version;

	std::vector<std::string> m_headerFiles;
	std::vector<std::string> m_cppFiles;
};
