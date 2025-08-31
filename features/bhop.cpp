#include "bhop.h"
#include "../core/input.h"
#include "../core/feature-base.h"

void runBhop(const BhopConfig& cfg, bool& toggle, bool& lastPressed) {
	runFeature(cfg, toggle, lastPressed, [&cfg]() {
		tapKey(cfg.jumpKey);
		});
}
