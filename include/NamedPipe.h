#pragma once

#include <functional>

void createAndRead(std::function<void(int, char *[])> &func);
void write();
