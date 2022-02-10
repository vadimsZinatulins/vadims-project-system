#include "Daemon.h"

#include <fstream>
#include <stdlib.h>
#include <unistd.h>

void createProcess()
{
	switch(fork())
	{
	case -1: exit(1);
	case 0: break;
	default: exit(0);
	}
}

void createPidFile()
{
	std::ofstream pidFile("/var/run/vps.pid");
	if(pidFile.fail())
	{
		exit(1);
	}

	pidFile << (long)getpid() << "\n";

	pidFile.close();
}

Daemon Daemon::m_instance;

Daemon &Daemon::getInstance() { return m_instance; }

bool Daemon::isRunning() const { return m_isRunning; }

void Daemon::daemonize() 
{
	createProcess();

	if(setsid() < 0)
		exit(1);

	createPidFile();

	m_isRunning = true;
}

void Daemon::stop() { m_isRunning = false; }
