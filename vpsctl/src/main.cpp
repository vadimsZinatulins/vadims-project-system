#include "Arguments.h"
#include "ArgProc.h"
#include "Daemon.h"
#include "NamedPipe.h"
#include "Workspace.h"
#include "WSManager.h"

#include <filesystem>
#include <csignal>
#include <iostream>
#include <unistd.h>

void daemonTerminate(int sig)
{
	std::cout << "Terminating" << std::endl;

	cleanup();
	Daemon::getInstance().shutdown();

	exit(1);
}

void initSignals()
{
	// Termination request, sent to the program
	std::signal(SIGTERM, daemonTerminate);
	// Invalid memory access (segmentation fault)
	std::signal(SIGSEGV, daemonTerminate);
	// External interrupt, usually initiated by the user
	std::signal(SIGINT, daemonTerminate);
	// Invalid program image, such as invalid instruction
	std::signal(SIGKILL, daemonTerminate);
	// Abnormal termination condition, as is e.g. initiated by std::abort()
	std::signal(SIGABRT, daemonTerminate);
	// Erroneous arithmetic operation such as divide by zero
	std::signal(SIGFPE, daemonTerminate);
}

void startDaemon()
{
	// Daemonize this process
	Daemon::getInstance().daemonize();

	// Initialize signals
	initSignals();

	// Workspace manager
	WSManager wsManager;

	// This is invoked whenever daemon receives an command
	createAndRead([&](int argCount, char *argValue[]){
		Arguments args(argCount, argValue);
		ArgProc actions;

		actions.add({ "--stop" }, []{ Daemon::getInstance().stop(); });

		while(args.hasMore()) 
		{
			auto nextArg = args.next();
			if(actions.contains(nextArg))
				actions[nextArg]();
		}
		
		std::filesystem::current_path("/");
	});

	Daemon::getInstance().shutdown();
}

void stopDaemon()
{
	write(Arguments({ "--stop" }));
}

void restartDaemon()
{
	stopDaemon();
	sleep(2);
	startDaemon();
}

int main(int argc, char *argv[])
{
	ArgProc actions;

	actions.add({ "--start" }, []{ startDaemon(); });
	actions.add({ "--stop" }, []{ stopDaemon(); });
	actions.add({ "--restart" }, []{ restartDaemon(); });

	Arguments args(argc, argv);
	while(args.hasMore()) 
	{
		auto nextArg = args.next();
		if(actions.contains(nextArg))
			actions[nextArg]();
	}

	return 0;
}
