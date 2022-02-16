#include "NamedPipe.h"
#include "Daemon.h"
#include "config.h"

#include <filesystem>
#include <functional>
#include <iostream>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#include <sys/file.h>
#include "sys/stat.h"

void NamedPipe::write(PipeType pipeType, std::string message)
{
	NamedPipe pipe;
	pipe.openPipe(pipeType);
	pipe.writeToPipe(message);
	pipe.close();
}

std::string NamedPipe::read(PipeType pipeType)
{
	NamedPipe pipe;
	pipe.openPipe(pipeType);
	std::string receivedMessage = pipe.readFromPipe();
	pipe.close();

	return receivedMessage;
}

void NamedPipe::openPipe(PipeType pipe, bool createPipe)
{
	std::string paths[2] = { VPSIN_PIPE_FILE, VPSOUT_PIPE_FILE };

	// Determine which pipe to open
	m_pipePath = paths[static_cast<int>(pipe)];

	// Create pipe if necessary
	if(createPipe && !std::filesystem::exists(m_pipePath) && mkfifo(m_pipePath.c_str(), 0622))
	{
		std::cout << "Failed to create named pipe at: " << m_pipePath << std::endl;
		return;
	}

	// Open the pipe
	m_namedPipe = open(m_pipePath.c_str(), O_RDWR);
	if(m_namedPipe < 0)
		std::cout << "Failed to open the pipe at: " << m_pipePath << std::endl;
}

void NamedPipe::close(bool deletePipe)
{
	// Close the pipe
	::close(m_namedPipe);

	// Delete the pipe if necessry
	if(deletePipe)
		remove(m_pipePath.c_str());
}

void NamedPipe::writeToPipe(std::string message)
{
	// Write arguments to the pipe
	::write(m_namedPipe, message.c_str(), message.size() + 1);
}

std::string NamedPipe::readFromPipe()
{
	// Pipe arguments
	char *pipeMessage = new char[PIPE_BUF];

	// Clear pipe buffer
	memset(pipeMessage, 0, PIPE_BUF);

	// Read from named pipe. If nothing is to read wait
	// until data comes up
	if(::read(m_namedPipe, pipeMessage, PIPE_BUF) < 0)
	{
		delete[] pipeMessage;

		return "";
	}

	std::string receivedMessage(pipeMessage);

	delete[] pipeMessage;

	return receivedMessage;
}

void NamedPipe::listenPipe(std::function<void(std::string)> onReceive)
{
	while(Daemon::getInstance().isRunning())
		onReceive(readFromPipe());
}

