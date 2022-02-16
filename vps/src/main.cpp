#include "Arguments.h"
#include "NamedPipe.h"

#include <filesystem>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
	std::vector<std::string> args(argv + 1, argv + argc);
	args.insert(args.begin(), "--change-dir " + std::filesystem::current_path().string());

	// Send input
	NamedPipe::write(PipeType::Input, Arguments(args).listArguments());

	// Wait output
	std::cout << NamedPipe::read(PipeType::Output) << std::endl;

	return 0;
}
