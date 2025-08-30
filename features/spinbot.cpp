#include "spinbot.h"
#include "../core/input.h"
#include "../core/feature-base.h"

void runSpinbot(const SpinbotConfig& cfg, bool& toggle, bool& lastPressed) {
	runFeatureWithFeedback(cfg, toggle, lastPressed, [&cfg]() {
		int dx = (cfg.direction == "left" ? -cfg.speed : cfg.speed);
		moveMouse(dx, 0);
		}, "Spinbot");
}
