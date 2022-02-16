#include "Daemon.h"
#include "PidFile.h"

#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

void createProcess()
{
	// Fork the process
	switch(fork())
	{
	case -1: exit(1);	// Exit on error
	case 0: break;		// Continue on child process
	default: exit(0);	// Exit the parent process
	}

	// Create session ID
	if(setsid() < 0)
		exit(1);		// Exit on error
}

Daemon Daemon::m_instance;

Daemon &Daemon::getInstance() { return m_instance; }

bool Daemon::isRunning() const { return m_isRunning; }

void Daemon::daemonize() 
{
	createProcess();

	// Create .pid file
	PidFile::open();

	m_isRunning = true;

	// Create input pipe file
	m_inputPipe.openPipe(PipeType::Input, true);

	// Create output pipe file
	m_outputPipe.openPipe(PipeType::Output, true);
}

void Daemon::shutdown() 
{
	// Delete .pid file
	PidFile::close();

	// Delete input pipe file
	m_inputPipe.close(true);

	// Delete output pipe file
	m_outputPipe.close(true);
}

void Daemon::stop() { m_isRunning = false; }
