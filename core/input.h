#pragma once
#include <windows.h>
#include <string>
#include "config.h"

extern DevConfig g_devConfig;

void tapKey(unsigned int vk);
void moveMouse(int dx, int dy);
bool setClipboardText(const std::string& text);
std::string getClipboardText();
void pasteFromClipboard();
