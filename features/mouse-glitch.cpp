#include "mouse-glitch.h"
#include "../src/input.h"
#include <cstdlib>
#include <ctime>

static bool seeded = false;

void runMouseGlitch(const MouseGlitchConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!cfg.enabled) return;

	if (!seeded) {
		srand(static_cast<unsigned int>(time(nullptr)));
		seeded = true;
	}

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
	if (cfg.mode == "toggle" && pressed && !lastPressed) toggle = !toggle;
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		int dx = rand() % (cfg.maxDistance * 2 + 1) - cfg.maxDistance;
		int dy = rand() % (cfg.maxDistance * 2 + 1) - cfg.maxDistance;
		moveMouse(dx, dy);
	}
}
