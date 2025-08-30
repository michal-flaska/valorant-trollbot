#pragma once
#include <windows.h>

void tapKey(unsigned int vk);
void tapMouse(unsigned int button); // left=0x01, right=0x02, back=0x05, forward=0x06
void moveMouse(int dx, int dy);
