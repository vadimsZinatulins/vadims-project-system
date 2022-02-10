#include "NamedPipe.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include <sys/file.h>
#include <sys/types.h>
#include "sys/stat.h"

void createAndRead()
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

	while(true)
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

		if(argc > 0) std::cout << "Got Arguments" << std::endl;
	}
}

void write()
{

}
