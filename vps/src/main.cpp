#include "Arguments.h"
#include "NamedPipe.h"

#include <filesystem>
#include <vector>

int main(int argc, char *argv[])
{
	std::vector<std::string> args(argv + 1, argv + argc);
	args.insert(args.begin(), "--change-dir " + std::filesystem::current_path().string());

	auto &namedPipe = NamedPipe::getInstance();

	namedPipe.openPipe(PipeType::Input, PipeAccess::Write);
	namedPipe.writeToPipe(args);
	namedPipe.close();

	return 0;
}
