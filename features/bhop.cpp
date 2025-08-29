#include "bhop.h"
#include "../src/input.h"
#include <thread>

void runBhop(const BhopConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
	if (cfg.mode == "toggle" && pressed && !lastPressed) toggle = !toggle;
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		Sleep(cfg.startDelay);
		if (cfg.jumpKey >= 0x01 && cfg.jumpKey <= 0x06)
			tapMouse(cfg.jumpKey);
		else
			tapKey(cfg.jumpKey);
		Sleep(cfg.repeatDelay);
	}
}
