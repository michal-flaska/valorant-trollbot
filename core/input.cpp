#include "input.h"
#include "logger.h"

bool tapKey(unsigned int vk) {
	INPUT inputs[2] = {};
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = static_cast<WORD>(vk);

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = static_cast<WORD>(vk);
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	const UINT result = SendInput(2, inputs, sizeof(INPUT));
	if (result != 2) {
		Logger::error("tapKey failed for VK: 0x" + std::to_string(vk));
		return false;
	}
	return true;
}

bool moveMouse(int dx, int dy) {
	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dx = dx;
	input.mi.dy = dy;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;

	const UINT result = SendInput(1, &input, sizeof(INPUT));
	if (result != 1) {
		Logger::error("moveMouse failed");
		return false;
	}
	return true;
}
