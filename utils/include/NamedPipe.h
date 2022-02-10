#pragma once

#include "Arguments.h"

#include <functional>

void createAndRead(std::function<void(int, char *[])> &func);
void write(Arguments args);
