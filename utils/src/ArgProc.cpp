#include "ArgProc.h"

void ArgProc::add(std::vector<std::string> list, std::function<void()> action)
{
	for(const auto &arg : list) m_actions[arg] = action;
}

std::function<void()> &ArgProc::operator[](std::string argument)
{
	return m_actions[argument];
}

bool ArgProc::contains(std::string argument) const
{
	return m_actions.find(argument) != m_actions.end();
}

