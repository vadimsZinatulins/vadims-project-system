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

	static void write(PipeType pipeType, std::string message);
	static std::string read(PipeType pipeType);

	void openPipe(PipeType pipe, bool createPipe = false);
	void close(bool deletePipe = false);

	void writeToPipe(std::string message);
	std::string readFromPipe();

	void listenPipe(std::function<void(std::string)> onReceive);
private:
	int m_namedPipe { 0 };

	std::string m_pipePath { "" };
};

