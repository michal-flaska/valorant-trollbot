#include "mouse-glitch.h"
#include "../src/input.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <cstdlib>

static std::atomic<bool> glitchToggle(false);

void startMouseGlitch(const MouseGlitchConfig& cfg) {
	std::thread([cfg]() {
		if (!cfg.enabled) return;

		while (true) {
			bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
			if (cfg.mode == "toggle") {
				static bool lastPressed = false;
				if (pressed && !lastPressed) glitchToggle = !glitchToggle;
				lastPressed = pressed;
			}

			if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && glitchToggle)) {
				int dx = (std::rand() % (cfg.maxDistance * 2 + 1)) - cfg.maxDistance;
				int dy = (std::rand() % (cfg.maxDistance * 2 + 1)) - cfg.maxDistance;
				moveMouse(dx, dy);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		}).detach();
}
