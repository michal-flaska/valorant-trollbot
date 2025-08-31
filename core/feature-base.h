#pragma once
#include "config.h"
#include "logger.h"
#include <windows.h>
#include <functional>

template<typename ConfigType>
class FeatureRunner {
private:
	bool toggle_ = false;
	bool lastPressed_ = false;

public:
	void run(const ConfigType& config, std::function<void()> action) {
		if (!config.enabled) return;

		const bool pressed = GetAsyncKeyState(config.triggerKey) & 0x8000;

		if (config.mode == "toggle" && pressed && !lastPressed_) {
			toggle_ = !toggle_;
			Logger::debug("Feature toggled: " + std::string(toggle_ ? "ON" : "OFF"));
		}
		lastPressed_ = pressed;

		if ((config.mode == "hold" && pressed) || (config.mode == "toggle" && toggle_)) {
			action();
		}
	}

	void runWithFeedback(const ConfigType& config, std::function<void()> action,
		const std::string& featureName) {
		if (!config.enabled) return;

		const bool pressed = GetAsyncKeyState(config.triggerKey) & 0x8000;

		if (config.mode == "toggle" && pressed && !lastPressed_) {
			toggle_ = !toggle_;
			Logger::info(featureName + " " + (toggle_ ? "ON" : "OFF"));
		}
		lastPressed_ = pressed;

		if ((config.mode == "hold" && pressed) || (config.mode == "toggle" && toggle_)) {
			action();
		}
	}
};
