#include "mouse-glitch.h"
#include "../core/input.h"
#include <uniform_int_distribution>

void MouseGlitch::run(const MouseGlitchConfig& config) {
	runner_.runWithFeedback(config, [this, &config]() {
		std::uniform_int_distribution<int> dist(-config.maxDistance, config.maxDistance);
		const int dx = dist(gen_);
		const int dy = dist(gen_);
		moveMouse(dx, dy);
		}, "Mouse Glitch");
}
