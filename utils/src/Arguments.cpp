#include "Arguments.h"
#include <vector>

Arguments::Arguments(int argc, char *argv[]) : m_arguments(std::move(std::vector<std::string>(argv + 1, argv + argc))), m_index(0) {}
Arguments::Arguments(std::vector<std::string> args) : m_arguments(std::move(args)) { }
Arguments::~Arguments() {}

bool Arguments::hasMore() const { return m_index < m_arguments.size(); }

std::string Arguments::next() { return m_arguments[m_index++]; }
