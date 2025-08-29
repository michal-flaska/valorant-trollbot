#include "spinbot.h"
#include "../src/input.h"

void runSpinbot(const SpinbotConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!cfg.enabled) return;

	bool pressed = GetAsyncKeyState(cfg.triggerKey) & 0x8000;
	if (cfg.mode == "toggle" && pressed && !lastPressed) toggle = !toggle;
	lastPressed = pressed;

	if ((cfg.mode == "hold" && pressed) || (cfg.mode == "toggle" && toggle)) {
		Sleep(cfg.startDelay);
		int dx = (cfg.direction == "left" ? -cfg.speed : cfg.speed);
		moveMouse(dx, 0);
		Sleep(cfg.interval);
	}
}
