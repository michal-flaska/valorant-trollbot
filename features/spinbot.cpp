#include "spinbot.h"
#include "../core/input.h"

void runSpinbot(const SpinbotConfig& cfg, FeatureRunner<SpinbotConfig>& runner) {
	runner.run(cfg, [&cfg]() {
		int dx = (cfg.direction == "left" ? -cfg.speed : cfg.speed);
		moveMouse(dx, 0);
		}, "Spinbot");
}
