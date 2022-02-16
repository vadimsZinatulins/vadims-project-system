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

void NamedPipe::writeToPipe(Arguments args)
{
	// Create the content to be writen to the pipe
	std::stringstream ss;
	while(args.hasMore()) ss << args.next() + " ";

	// Write arguments to the pipe
	write(m_namedPipe, ss.str().c_str(), ss.str().size() + 1);
}

Arguments NamedPipe::readFromPipe()
{
	// Pipe arguments
	char *cmdPipe = new char[PIPE_BUF];

	// Argument list
	char **argv = new char*[PIPE_BUF * sizeof(char*)];

	// Clear pipe buffer
	memset(cmdPipe, 0, PIPE_BUF);

	// Read from named pipe. If nothing is to read wait
	// until data comes up
	if(read(m_namedPipe, cmdPipe, PIPE_BUF) < 0)
	{
		delete[] cmdPipe;
		delete[] argv;

		return Arguments({});
	}

	// Tokenize pipe arguments
	char *arg = strtok(cmdPipe, " \t\n");
	int argc = 1;

	// Store arguments in argv list
	while(arg != nullptr && argc < PIPE_BUF)
	{
		argv[argc++] = arg;
		arg = strtok(nullptr, " \t\n");
	}

	Arguments args(argc, argv);

	delete[] cmdPipe;
	delete[] argv;

	return args;
}

void NamedPipe::listenPipe(std::function<void(Arguments)> onReceive)
{
	while(Daemon::getInstance().isRunning())
		onReceive(readFromPipe());
}

