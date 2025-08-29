#include "input.h"

void pressKey(WORD key) {
	INPUT input{};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	SendInput(1, &input, sizeof(INPUT));
}

void releaseKey(WORD key) {
	INPUT input{};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

void tapKey(WORD key) {
	pressKey(key);
	releaseKey(key);
}

void moveMouse(int dx, int dy) {
	INPUT input{};
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = dx;
	input.mi.dy = dy;
	SendInput(1, &input, sizeof(INPUT));
}
