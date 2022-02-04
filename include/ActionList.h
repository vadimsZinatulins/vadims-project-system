#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

using ActionList = std::unordered_map<std::string, std::function<void()>>;

void insertAction(ActionList &list, std::vector<std::string> aliases, std::function<void()> action);
