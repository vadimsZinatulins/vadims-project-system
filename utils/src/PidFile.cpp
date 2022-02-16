#include "PidFile.h"

#include <fstream>
#include <unistd.h>

void PidFile::open()
{
	std::ofstream pidFile("/tmp/vps.pid");
	if(pidFile.fail())
	{
		exit(1);
	}

	pidFile << (long)getpid() << "\n";

	pidFile.close();
}

void PidFile::close()
{
	remove("/tmp/vps.pid");
}
