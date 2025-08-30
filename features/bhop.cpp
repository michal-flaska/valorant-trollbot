#include "bhop.h"
#include "../core/input.h"

void runBhop(const BhopConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
	if (cfg.mode == "toggle" && pressed && !lastPressed) toggle = !toggle;
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		// Jump key is always a keyboard key (Space = 0x20)
		tapKey(cfg.jumpKey);
	}
}
