#include "spinbot.h"
#include "../src/input.h"
#include <thread>
#include <atomic>
#include <chrono>

static std::atomic<bool> spinToggle(false);

void startSpinbot(const SpinbotConfig& cfg) {
	std::thread([cfg]() {
		if (!cfg.enabled) return;

		bool lastPressed = false;
		int dx = (cfg.direction == "left") ? -cfg.speed : cfg.speed;

		while (true) {
			bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;

			if (cfg.mode == "toggle") {
				if (pressed && !lastPressed) spinToggle = !spinToggle;
				lastPressed = pressed;
			}

			if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && spinToggle)) {
				std::this_thread::sleep_for(std::chrono::milliseconds(cfg.startDelay));
				moveMouse(dx, 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(cfg.interval));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		}).detach();
}
