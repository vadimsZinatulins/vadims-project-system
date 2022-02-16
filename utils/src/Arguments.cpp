#include "Arguments.h"
#include <iostream>
#include <vector>
#include <sstream>

Arguments::Arguments(int argc, char *argv[]) : m_arguments(std::move(std::vector<std::string>(argv + 1, argv + argc))), m_index(0) {}
Arguments::Arguments(std::string arguments)  : m_index(0)
{
	std::stringstream buffer(arguments);
	for(std::string arg; buffer >> arg; ) 
		m_arguments.push_back(arg);
}

Arguments::Arguments(std::vector<std::string> args) : m_arguments(std::move(args)), m_index(0) {}
Arguments::~Arguments() {}

bool Arguments::hasMore() const { return m_index < m_arguments.size(); }

std::string Arguments::next() { return m_arguments[m_index++]; }

void Arguments::print() const { std::cout << "Arguments: " << std::endl; for(const auto &a : m_arguments) std::cout << "\t" << a; std::cout << std::endl; }

std::string Arguments::listArguments() const
{
	std::stringstream buffer;
	for(const auto &e : m_arguments) buffer << e << " ";
	return buffer.str();
}
