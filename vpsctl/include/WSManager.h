#pragma once

#include <unordered_map>
#include <memory>

class Workspace;

using WSManager = std::unordered_map<std::string, std::shared_ptr<Workspace>>;
