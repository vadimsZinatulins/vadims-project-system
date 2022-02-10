#include "Arguments.h"
#include "ArgProc.h"
#include "Daemon.h"
#include "NamedPipe.h"

#include <signal.h>
#include <stdlib.h>

void daemonTerminate(int sig)
{
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

	ArgProc actions;

	actions.add({ "--stop" }, []{ Daemon::getInstance().stop(); });

	createAndRead([&](int argc, char *argv[]){
		Arguments args(argc, argv);
		while(args.hasMore()) 
		{
			auto nextArg = args.next();
			if(actions.contains(nextArg))
				actions[nextArg]();
		}
	});

	Daemon::getInstance().shutdown();

	return 0;
}
