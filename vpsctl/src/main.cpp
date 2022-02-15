#include "Arguments.h"
#include "ArgProc.h"
#include "Daemon.h"
#include "NamedPipe.h"
#include "Workspace.h"
#include "WSManager.h"

#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>

void daemonTerminate(int sig)
{
	cleanup();
	Daemon::getInstance().shutdown();

	exit(1);
}

void initSignals()
{
	signal(SIGINT, daemonTerminate);
	signal(SIGTERM, daemonTerminate);

	signal(SIGCHLD, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
}

int main(int argc, char *argv[])
{
	Daemon::getInstance().daemonize();

	initSignals();

	WSManager wsManager;

	createAndRead([&](int argCount, char *argValue[]){
		Arguments args(argCount, argValue);
		ArgProc actions;

		actions.add({ "--stop" }, []{ Daemon::getInstance().stop(); });
		actions.add({ "--init" }, [&]{ Workspace::create(args.next(), wsManager); });
		actions.add({ "--change-dir" }, [&]{ std::filesystem::current_path(args.next()); });
		actions.add({ "--new-workspace", "--nw" }, []{});
		actions.add({ "--new-app", "--na" }, []{});
		actions.add({ "--new-lib", "--nl" }, []{});
		actions.add({ "--add-header", "--ah" }, []{});
		actions.add({ "--add-cpp", "--ac" }, []{});
		actions.add({ "--add-header-cpp", "--ahc" }, []{});

		while(args.hasMore()) 
		{
			auto nextArg = args.next();
			if(actions.contains(nextArg))
			{
				actions[nextArg]();
			}
		}
		
		std::filesystem::current_path("/");
	});

	Daemon::getInstance().shutdown();

	return 0;
}
