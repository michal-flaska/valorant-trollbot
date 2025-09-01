#include "input.h"
#include <winuser.h>

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
		input.mi.time = 0;
		input.mi.dwExtraInfo = GetMessageExtraInfo();
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
		mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, GetMessageExtraInfo());
		break;
	}
	case 3: {
		POINT pos;
		if (GetPhysicalCursorPos(&pos)) {
			SetPhysicalCursorPos(pos.x + dx, pos.y + dy);
		}
		break;
	}
	case 4: {
		INPUT input = {};
		input.type = INPUT_MOUSE;
		input.mi.dx = dx;
		input.mi.dy = dy;
		input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_MOVE_NOCOALESCE;
		input.mi.time = GetTickCount();
		input.mi.dwExtraInfo = 0;
		SendInput(1, &input, sizeof(INPUT));
		break;
	}
	case 5: {
		INPUT input = {};
		input.type = INPUT_MOUSE;
		input.mi.dx = dx;
		input.mi.dy = dy;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		input.mi.time = 0;
		input.mi.dwExtraInfo = 0;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(1);
		break;
	}
	case 6: {
		static HANDLE hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		SetEvent(hEvent);
		mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, reinterpret_cast<ULONG_PTR>(hEvent));
		break;
	}
	}
}
