#include "inspect-spam.h"
#include "../src/input.h"

void runInspect(const InspectConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
	if (cfg.mode == "toggle" && pressed && !lastPressed) toggle = !toggle;
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		// Inspect key is always a keyboard key (ALT = 0x12)
		tapKey(cfg.inspectKey);
	}
}
