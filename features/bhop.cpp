#include "bhop.h"
#include "../core/input.h"

void runBhop(const BhopConfig& cfg, FeatureRunner<BhopConfig>& runner) {
	runner.run(cfg, [&cfg]() {
		tapKey(cfg.jumpKey);
		}, "Bhop");
}
