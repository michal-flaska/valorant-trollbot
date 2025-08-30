#include "spinbot.h"
#include "../core/input.h"
#include <iostream>

void runSpinbot(const SpinbotConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
	if (cfg.mode == "toggle" && pressed && !lastPressed) {
		toggle = !toggle;
		std::cout << "Spinbot " << (toggle ? "ON" : "OFF") << '\n';
	}
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		int dx = (cfg.direction == "left" ? -cfg.speed : cfg.speed);
		moveMouse(dx, 0);
	}
}
