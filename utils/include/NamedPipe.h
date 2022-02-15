#pragma once

#include "Arguments.h"

#include <functional>
#include <string>

enum class PipeType { Input, Output };
enum class PipeAccess { Read, Write };

class NamedPipe final 
{
public:
	static NamedPipe &getInstance();

	void openPipe(PipeType pipe, PipeAccess acces, bool createPipe = false);
	void close(bool deletePipe = false);

	void writeToPipe(Arguments args);
	Arguments readFromPipe();

	void listenPipe(std::function<void(Arguments)> onReceive);
private:
	NamedPipe() = default;
	~NamedPipe() = default;

	static NamedPipe m_instance;

	int m_namedPipe { 0 };

	std::string m_pipePath { "" };
	int m_pipeAccess { 0 };
};

