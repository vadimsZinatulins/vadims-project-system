#include "Arguments.h"
#include "NamedPipe.h"

#include <filesystem>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
	std::vector<std::string> args(argv + 1, argv + argc);
	args.insert(args.begin(), "--change-dir " + std::filesystem::current_path().string());

	NamedPipe inputPipe;
	inputPipe.openPipe(PipeType::Input);
	inputPipe.writeToPipe(args);
	inputPipe.close();

	NamedPipe outputPipe;
	outputPipe.openPipe(PipeType::Output);
	auto outputArgs = outputPipe.readFromPipe();
	outputPipe.close();

	while(outputArgs.hasMore()) std::cout << outputArgs.next();

	return 0;
}
