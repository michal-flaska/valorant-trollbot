#include "inspect-spam.h"
#include "../core/input.h"

void runInspect(const InspectConfig& cfg, FeatureRunner<InspectConfig>& runner) {
	runner.run(cfg, [&cfg]() {
		tapKey(cfg.inspectKey);
		}, "Inspect Spam");
}
