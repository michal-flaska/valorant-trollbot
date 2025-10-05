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

bool setClipboardText(const std::string& text) {
	if (!OpenClipboard(nullptr)) return false;

	if (!EmptyClipboard()) {
		CloseClipboard();
		return false;
	}

	size_t size = text.length() + 1;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, size);
	if (!hGlobal) {
		CloseClipboard();
		return false;
	}

	char* pGlobal = static_cast<char*>(GlobalLock(hGlobal));
	if (!pGlobal) {
		GlobalFree(hGlobal);
		CloseClipboard();
		return false;
	}

	strcpy_s(pGlobal, size, text.c_str());
	GlobalUnlock(hGlobal);

	if (!SetClipboardData(CF_TEXT, hGlobal)) {
		GlobalFree(hGlobal);
		CloseClipboard();
		return false;
	}

	CloseClipboard();
	return true;
}

std::string getClipboardText() {
	if (!IsClipboardFormatAvailable(CF_TEXT) || !OpenClipboard(nullptr)) {
		return "";
	}

	HANDLE hData = GetClipboardData(CF_TEXT);
	if (!hData) {
		CloseClipboard();
		return "";
	}

	char* pszText = static_cast<char*>(GlobalLock(hData));
	if (!pszText) {
		CloseClipboard();
		return "";
	}

	std::string result(pszText);
	GlobalUnlock(hData);
	CloseClipboard();

	return result;
}

void pasteFromClipboard() {
	INPUT inputs[4] = {};

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_CONTROL;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = 'V';

	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = 'V';
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = VK_CONTROL;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(4, inputs, sizeof(INPUT));
}
