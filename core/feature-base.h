#pragma once
#include "config.h"
#include <windows.h>
#include <functional>
#include <iostream>
#include <chrono>

extern DevConfig g_devConfig;

template<typename ConfigType>
class FeatureRunner {
private:
	bool toggle = false;
	bool lastPressed = false;
	std::chrono::steady_clock::time_point lastActionTime;
	bool hasDelayPassed = false;

public:
	void run(const ConfigType& cfg, std::function<void()> action, const char* featureName = nullptr) {
		if (!cfg.enabled) return;

		bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;

		if (cfg.mode == "toggle" && pressed && !lastPressed) {
			toggle = !toggle;
			hasDelayPassed = false;
			lastActionTime = std::chrono::steady_clock::now();

			if (featureName && g_devConfig.showToggleLogs) {
				std::cout << featureName << " " << (toggle ? "ON" : "OFF") << '\n';
			}
		}
		lastPressed = pressed;

		bool shouldExecute = (cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle);

		if (shouldExecute) {
			auto now = std::chrono::steady_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastActionTime).count();

			if (!hasDelayPassed) {
				if (elapsed >= cfg.startDelay) {
					hasDelayPassed = true;
					lastActionTime = now;
					action();
				}
			}
			else {
				if (elapsed >= cfg.repeatDelay) {
					lastActionTime = now;
					action();
				}
			}
		}
		else {
			hasDelayPassed = false;
		}
	}

	void reset(const char* featureName = nullptr) {
		if (toggle) {
			toggle = false;
			hasDelayPassed = false;
			if (featureName && g_devConfig.showToggleLogs) {
				std::cout << featureName << " OFF\n";
			}
		}
	}

	bool isActive() const {
		return toggle;
	}
};
