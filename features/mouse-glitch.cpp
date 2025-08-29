#include "mouse-glitch.h"
#include "../src/input.h"
#include <cstdlib>

void runMouseGlitch(const MouseGlitchConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
	if (cfg.mode == "toggle" && pressed && !lastPressed) toggle = !toggle;
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		Sleep(cfg.startDelay);
		int dx = rand() % (cfg.maxDistance * 2 + 1) - cfg.maxDistance;
		int dy = rand() % (cfg.maxDistance * 2 + 1) - cfg.maxDistance;
		moveMouse(dx, dy);
		Sleep(cfg.repeatDelay);
	}
}
