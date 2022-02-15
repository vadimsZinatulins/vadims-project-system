#include "Workspace.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <streambuf>
#include <cstring>

void Workspace::create(std::string name, WSManager &wsManager)
{
	// If the current path already exists in the wsManager or the .vps exists
	// then the workspace was already initialized
	if(wsManager.find(std::filesystem::current_path()) != wsManager.end() || std::filesystem::exists(".vps"))
		return;

	auto ws = std::make_shared<Workspace>();

	ws->m_name = name;
	ws->setMajorVersion(1);
	ws->setMinorVersion(0);

	ws->createFile();

	wsManager[std::filesystem::current_path()] = ws;
}

Workspace::Workspace() {}
Workspace::Workspace(std::string path) {}
Workspace::~Workspace() {}

void Workspace::setMajorVersion(unsigned int version) 
{
	m_version = (m_version & 0x0f) | ((version & 0x0f) << 4);
}

void Workspace::setMinorVersion(unsigned int version) 
{
	m_version = (m_version & 0xf0) | (version & 0x0f);
}

unsigned int Workspace::getMajorVerion() const 
{
	return (m_version & 0xf0) >> 4;
}

unsigned int Workspace::getMinorVersion() const 
{
	return m_version & 0x0f;
}

void Workspace::createFile() const
{
	Buffer buffer = serialize();

	std::ofstream configFile(".vps", std::ios::binary | std::ios::trunc);
	configFile.write(buffer.data, buffer.size);
	configFile.close();
}

Workspace::Buffer Workspace::serialize() const
{
	// Calculate the buffer size
	std::size_t bufferSize { sizeof(char) + m_name.size() + 3 };
	for(const auto &hf : m_headerFiles) bufferSize += hf.size() + 1;
	for(const auto &sf : m_cppFiles) bufferSize += sf.size() + 1;

	// Allocate the buffer
	char *buffer = new char[bufferSize];

	// Indicates the next index of the buffer where to store data
	std::size_t index { sizeof(char) };

	// Store version in the buffer
	std::memcpy(buffer, &m_version, sizeof(char));

	// Store the name of the workspace in the buffer
	std::memcpy(buffer + index, m_name.c_str(), m_name.size());

	// Advance with the index
	index += m_name.size() + 1;

	// Store the number of header files into the buffer
	auto numHeaders = m_headerFiles.size();
	std::memcpy(buffer + index, &numHeaders, 1);

	// Store all header files in the buffer
	for(const auto &hf : m_headerFiles)
	{
		auto fileSize = hf.size();
		std::memcpy(buffer + index, hf.c_str(), fileSize);
		index += fileSize + 1;
	}

	// Store the number of source files into the buffer
	auto numSources = m_cppFiles.size();
	std::memcpy(buffer + index, &numSources, 1);

	// Store all source files in the buffer
	for(const auto &sf : m_cppFiles)
	{
		auto fileSize = sf.size();
		std::memcpy(buffer + index, sf.c_str(), fileSize);
		index += fileSize + 1;
	}

	return { buffer, bufferSize };
}

void Workspace::deserialize(Workspace::Buffer buffer)
{

}

