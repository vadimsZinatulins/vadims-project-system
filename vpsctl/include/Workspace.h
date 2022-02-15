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
private:
	struct Buffer
	{
		void *data;
		std::size_t size;
	};

	void createFile() const;

	Buffer serialize();
	void deserialize(Buffer buffer);

	std::string m_name;

	int m_majorVersion;
	int m_minorVersion;

	std::vector<std::string> m_headerFiles;
	std::vector<std::string> m_cppFiles;
};
