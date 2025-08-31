#pragma once
#include "config.h"
#include <windows.h>
#include <functional>
#include <iostream>

// Generic feature runner that handles common trigger/toggle logic
template<typename ConfigType>
void runFeature(const ConfigType& cfg, bool& toggle, bool& lastPressed, std::function<void()> action) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;

	// Handle toggle mode state change
	if (cfg.mode == "toggle" && pressed && !lastPressed) {
		toggle = !toggle;
	}
	lastPressed = pressed;

	// Execute action based on mode
	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		action();
	}
}

// Specialized version for features that need toggle feedback
template<typename ConfigType>
void runFeatureWithFeedback(const ConfigType& cfg, bool& toggle, bool& lastPressed,
	std::function<void()> action, const char* featureName) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;

	if (cfg.mode == "toggle" && pressed && !lastPressed) {
		toggle = !toggle;
		if (featureName) {
			std::cout << featureName << " " << (toggle ? "ON" : "OFF") << '\n';
		}
	}
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		action();
	}
}
