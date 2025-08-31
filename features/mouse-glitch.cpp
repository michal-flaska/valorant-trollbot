#include "mouse-glitch.h"
#include "../core/input.h"
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

void runMouseGlitch(const MouseGlitchConfig& cfg, FeatureRunner<MouseGlitchConfig>& runner) {
	runner.run(cfg, [&cfg]() {
		std::uniform_int_distribution<int> dist(-cfg.maxDistance, cfg.maxDistance);
		int dx = dist(gen);
		int dy = dist(gen);
		moveMouse(dx, dy);
		}, "Mouse Glitch");
}
