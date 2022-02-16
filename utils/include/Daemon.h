#pragma once

#include "NamedPipe.h"

class Daemon final
{
public:
	static Daemon &getInstance();

	bool isRunning() const;

	void daemonize();
	void shutdown();

	void stop();

	NamedPipe m_inputPipe;
	NamedPipe m_outputPipe;
private:
	Daemon() = default;
	~Daemon() = default;

	static Daemon m_instance;

	bool m_isRunning { false };
};
