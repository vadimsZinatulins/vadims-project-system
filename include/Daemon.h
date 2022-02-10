#pragma once

class Daemon final
{
public:
	static Daemon &getInstance();

	bool isRunning() const;

	void daemonize();
	void stop();
private:
	Daemon() = default;
	~Daemon() = default;

	static Daemon m_instance;

	bool m_isRunning { false };
};
