#pragma once

#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

class ArgProc final 
{
public:
	ArgProc() = default;
	~ArgProc() = default;

	void add(std::vector<std::string> list, std::function<void()> action);

	std::function<void()> &operator[](std::string argument);

	bool contains(std::string argument) const;
private:
	std::unordered_map<std::string, std::function<void()>> m_actions;
};
