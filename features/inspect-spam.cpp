#include "inspect-spam.h"
#include "../src/input.h"
#include <thread>

void runInspect(const InspectConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
	if (cfg.mode == "toggle" && pressed && !lastPressed) toggle = !toggle;
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		Sleep(cfg.startDelay);
		if (cfg.inspectKey >= 0x01 && cfg.inspectKey <= 0x06)
			tapMouse(cfg.inspectKey);
		else
			tapKey(cfg.inspectKey);
		Sleep(cfg.repeatDelay);
	}
}
