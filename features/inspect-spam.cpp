#include "inspect-spam.h"
#include "../src/input.h"
#include <thread>
#include <atomic>
#include <chrono>

static std::atomic<bool> toggleInspect(false);

void startInspectSpam(const InspectConfig& cfg) {
	std::thread([cfg]() {
		if (!cfg.enabled) return;

		bool lastPressed = false;

		while (true) {
			bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;

			if (cfg.mode == "toggle") {
				if (pressed && !lastPressed) toggleInspect = !toggleInspect;
				lastPressed = pressed;
			}

			if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggleInspect)) {
				std::this_thread::sleep_for(std::chrono::milliseconds(cfg.startDelay));
				tapKey(cfg.inspectKey);
				std::this_thread::sleep_for(std::chrono::milliseconds(cfg.repeatDelay));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		}).detach();
}
