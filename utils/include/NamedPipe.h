#pragma once

#include "Arguments.h"

#include <functional>

void createAndRead(std::function<void(int, char *[])> func);
void cleanup();

void write(Arguments args);
