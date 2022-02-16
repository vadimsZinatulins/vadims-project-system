#pragma once

#include "Arguments.h"

#include <functional>
#include <string>

enum class PipeType { Input = 0, Output = 1 };

class NamedPipe final 
{
public:
	NamedPipe() = default;
	~NamedPipe() = default;

	void openPipe(PipeType pipe, bool createPipe = false);
	void close(bool deletePipe = false);

	void writeToPipe(Arguments args);
	Arguments readFromPipe();

	void listenPipe(std::function<void(Arguments)> onReceive);
private:
	int m_namedPipe { 0 };

	std::string m_pipePath { "" };
};

