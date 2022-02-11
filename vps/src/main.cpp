#include "Arguments.h"
#include "NamedPipe.h"

#include <iostream>
#include <filesystem>
#include <utility>
#include <vector>

int main(int argc, char *argv[])
{
	std::vector<std::string> args(argv + 1, argv + argc);
	args.insert(args.begin(), "--change-dir " + std::filesystem::current_path().string());

	write(args);

	return 0;
}
