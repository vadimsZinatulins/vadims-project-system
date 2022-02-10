#pragma once

#include <string>
#include <vector>

class Arguments final
{
public:
	Arguments(int argc, char *argv[]);
	Arguments(std::vector<std::string> args);
	~Arguments();

	bool hasMore() const;
	std::string next();
private:
	std::vector<std::string> m_arguments;
	std::size_t m_index;
};

