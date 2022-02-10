#include "Daemon.h"

#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

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
	std::ofstream pidFile("/tmp/vps.pid");
	if(pidFile.fail())
	{
		std::cout << "Failed to open pid file" << std::endl;
		exit(1);
	}

	pidFile << (long)getpid() << "\n";

	pidFile.close();
}

Daemon Daemon::m_instance;

Daemon &Daemon::getInstance() { return m_instance; }

#include <iostream>
bool Daemon::isRunning() const { std::cout << "Checking if still running" << std::endl; return m_isRunning; }

void Daemon::daemonize() 
{
	std::cout << "Creating process" << std::endl;
	createProcess();
	std::cout << "Process created" << std::endl;

	std::cout << "Creating session" << std::endl;
	if(setsid() < 0)
	{
		std::cout << "Failed to create session" << std::endl;
		exit(1);
	}
	std::cout << "Session created" << std::endl;

	std::cout << "Creating pid file" << std::endl;
	createPidFile();
	std::cout << "Pid file created" << std::endl;

	m_isRunning = true;
}

void Daemon::stop() { std::cout << "Stoping Daemon Call" << std::endl; m_isRunning = false; exit(1); }
