#include "config.h"
#include "Arguments.h"
#include "ActionList.h"
#include "NewProject.h"

#include <iostream>
#include <filesystem>

int main(int argc, char *argv[])
{
	std::cout << "Running VPS version: " << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;

	Arguments args(argc, argv);
	ActionList al;

	insertAction(al, { "--help", "-h"} , []{ std::cout << "Print Help" << std::endl; });
	insertAction(al, { "--new", "-n"} , [&]{ NewProject(args.next()).create(); });

	while(args.hasMore()) al[args.next()]();

	return 0;
}

