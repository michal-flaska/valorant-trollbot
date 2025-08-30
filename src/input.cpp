#include "input.h"

void tapKey(unsigned int vk) {
	INPUT inputs[2] = {};
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = static_cast<WORD>(vk);
	inputs[0].ki.dwFlags = 0;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = static_cast<WORD>(vk);
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2, inputs, sizeof(INPUT));
}

void tapMouse(unsigned int button) {
	INPUT inputs[2] = {};
	inputs[0].type = INPUT_MOUSE;
	inputs[1].type = INPUT_MOUSE;

	switch (button) {
	case 0x01:
		inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		break;
	case 0x02:
		inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		break;
	case 0x04:
		inputs[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		break;
	case 0x05:
		inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[0].mi.mouseData = XBUTTON1;
		inputs[1].mi.mouseData = XBUTTON1;
		break;
	case 0x06:
		inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_XUP;
		inputs[0].mi.mouseData = XBUTTON2;
		inputs[1].mi.mouseData = XBUTTON2;
		break;
	}
	SendInput(2, inputs, sizeof(INPUT));
}

void moveMouse(int dx, int dy) {
	// Try multiple approaches for better compatibility

	// Method 1: Standard relative movement
	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dx = dx;
	input.mi.dy = dy;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(INPUT));

	// Method 2: Direct cursor position manipulation as fallback
	if (dx != 0 || dy != 0) {
		POINT currentPos;
		if (GetCursorPos(&currentPos)) {
			SetCursorPos(currentPos.x + dx, currentPos.y + dy);
		}
	}
}
