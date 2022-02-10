#include "Arguments.h"
#include "ArgProc.h"
#include "Daemon.h"
#include "NamedPipe.h"

#include <signal.h>
#include <iostream>

void daemonTerminate(int sig)
{
	Daemon::getInstance().stop();
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

	createAndRead([](int argc, char *argv[]){
		Arguments args(argc, argv);
		while(args.hasMore()) std::cout << args.next() << std::endl;
	});

	return 0;
}
