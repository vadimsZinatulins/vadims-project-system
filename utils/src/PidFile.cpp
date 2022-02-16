#include "PidFile.h"
#include "config.h"

#include <fstream>
#include <unistd.h>

void PidFile::open()
{
	std::ofstream pidFile(VPSPID_FILE);
	if(pidFile.fail())
	{
		exit(1);
	}

	pidFile << (long)getpid() << "\n";

	pidFile.close();
}

void PidFile::close()
{
	remove(VPSPID_FILE);
}
