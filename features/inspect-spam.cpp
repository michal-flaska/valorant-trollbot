#include "inspect-spam.h"
#include "../src/input.h"
#include <thread>
#include <atomic>
#include <chrono>

static std::atomic<bool> inspectToggle(false);

void startInspectSpam(const InspectConfig& cfg) {
	std::thread([cfg]() {
		if (!cfg.enabled) return;

		while (true) {
			bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
			if (cfg.mode == "toggle") {
				static bool lastPressed = false;
				if (pressed && !lastPressed) inspectToggle = !inspectToggle;
				lastPressed = pressed;
			}

			if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && inspectToggle)) {
				tapKey(cfg.inspectKey);
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		}).detach();
}
