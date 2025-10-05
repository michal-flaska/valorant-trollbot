#pragma once
#include <windows.h>
#include <string>

void tapKey(unsigned int vk);
bool setClipboardText(const std::string& text);
std::string getClipboardText();
void pasteFromClipboard();
