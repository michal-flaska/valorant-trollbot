#include "input.h"

void tapKey(unsigned int vk) {
	INPUT inputs[2] = {};
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = static_cast<WORD>(vk);

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = static_cast<WORD>(vk);
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(2, inputs, sizeof(INPUT));
}

void moveMouse(int dx, int dy) {
	switch (g_devConfig.mouseMethod) {
	case 0: {
		INPUT input = {};
		input.type = INPUT_MOUSE;
		input.mi.dx = dx;
		input.mi.dy = dy;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case 1: {
		POINT pos;
		if (GetCursorPos(&pos)) {
			SetCursorPos(pos.x + dx, pos.y + dy);
		}
		break;
	}
	case 2: {
		mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, 0);
		break;
	}
	case 3: {
		static int counter = 0;
		counter++;
		switch (counter % 3) {
		case 0: {
			INPUT input = {};
			input.type = INPUT_MOUSE;
			input.mi.dx = dx;
			input.mi.dy = dy;
			input.mi.dwFlags = MOUSEEVENTF_MOVE;
			SendInput(1, &input, sizeof(INPUT));
			break;
		}
		case 1: {
			POINT pos;
			if (GetCursorPos(&pos)) {
				SetCursorPos(pos.x + dx, pos.y + dy);
			}
			break;
		}
		case 2: {
			mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, 0);
			break;
		}
		}
		break;
	}
	}
}
