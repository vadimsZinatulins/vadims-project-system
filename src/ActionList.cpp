#include "ActionList.h"

void insertAction(ActionList &list, std::vector<std::string> aliases, std::function<void()> action)
{
	for(const auto &alias : aliases) list[alias] = action;
}
