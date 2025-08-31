#include "spinbot.h"
#include "../core/input.h"

void Spinbot::run(const SpinbotConfig& config) {
	runner_.runWithFeedback(config, [&config]() {
		const int dx = (config.direction == "left" ? -config.speed : config.speed);
		moveMouse(dx, 0);
		}, "Spinbot");
}
