#include "mouse-glitch.h"
#include "../src/input.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <cstdlib>

static std::atomic<bool> toggleGlitch(false);

void startMouseGlitch(const MouseGlitchConfig& cfg) {
	std::thread([cfg]() {
		if (!cfg.enabled) return;

		bool lastPressed = false;

		while (true) {
			bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;

			if (cfg.mode == "toggle") {
				if (pressed && !lastPressed) toggleGlitch = !toggleGlitch;
				lastPressed = pressed;
			}

			if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggleGlitch)) {
				std::this_thread::sleep_for(std::chrono::milliseconds(cfg.startDelay));

				int dx = (std::rand() % (cfg.maxDistance * 2 + 1)) - cfg.maxDistance;
				int dy = (std::rand() % (cfg.maxDistance * 2 + 1)) - cfg.maxDistance;
				moveMouse(dx, dy);

				std::this_thread::sleep_for(std::chrono::milliseconds(cfg.repeatDelay));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		}).detach();
}
