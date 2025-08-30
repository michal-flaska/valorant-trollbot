#include "mouse-glitch.h"
#include "../core/input.h"
#include "../core/feature-base.h"
#include <cstdlib>
#include <ctime>

static bool seeded = false;

void runMouseGlitch(const MouseGlitchConfig& cfg, bool& toggle, bool& lastPressed) {
	if (!seeded) {
		srand(static_cast<unsigned int>(time(nullptr)));
		seeded = true;
	}

	runFeatureWithFeedback(cfg, toggle, lastPressed, [&cfg]() {
		int dx = rand() % (cfg.maxDistance * 2 + 1) - cfg.maxDistance;
		int dy = rand() % (cfg.maxDistance * 2 + 1) - cfg.maxDistance;
		moveMouse(dx, dy);
		}, "Mouse Glitch");
}
