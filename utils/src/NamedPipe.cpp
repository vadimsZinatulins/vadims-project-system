#include "NamedPipe.h"
#include "Daemon.h"

#include <fcntl.h>
#include <functional>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <sys/file.h>
#include <sys/types.h>
#include "sys/stat.h"

void createAndRead(std::function<void(int, char *[])> &func)
{
	// Create named pipe
	if(mkfifo("/tmp/vps.pipe", 0622) != 0)
	{
		std::cout << "Failed to create named pipe" << std::endl;
		return;
	}

	// Open named pipe
	int namedPipe = open("/tmp/vps.pipe", O_RDWR);
	if(namedPipe < 0)
	{
		std::cout << "Failed to open named pipe" << std::endl;
		return;
	}

	// Pipe arguments
	char *cmdPipe = (char *)malloc(PIPE_BUF);

	// Argument list
	char **argv = (char **)malloc(PIPE_BUF * sizeof(char *));

	// While daemon is running
	while(Daemon::getInstance().isRunning())
	{
		// Clear pipe buffer
		memset(cmdPipe, 0, PIPE_BUF);

		// Read from named pipe. If nothing is to read wait
		// until data comes up
		if(read(namedPipe, cmdPipe, PIPE_BUF) < 0)
			return;

		// Tokenize pipe arguments
		char *arg = strtok(cmdPipe, " \t\n");
		int argc = 1;

		// Store arguments in argv list
		while(arg != nullptr && argc < PIPE_BUF)
		{
			argv[argc++] = arg;
			arg = strtok(nullptr, " \t\n");
		}

		if(argc > 0) func(argc, argv);
	}

	// Close named pipe
	close(namedPipe);

	// Delete the named pipe
	remove("/tmp/vps.pipe");
}

void write(Arguments args)
{
	// Open named pipe
	int pipeFile = open("/tmp/vps.pipe", O_RDONLY);
	// Check if it was successfully opened
	if(pipeFile < 0)
		return;

	// Write arguments to the named pipe
	while(args.hasMore())
	{
		auto arg = args.next() + "\n";
		write(pipeFile, arg.c_str(), arg.size() + 1);
	}

	// Close named pipe
	close(pipeFile);
}

