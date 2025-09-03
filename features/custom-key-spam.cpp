#include "custom-key-spam.h"
#include "../core/input.h"

void runCustomKeySpam(const CustomKeySpamConfig& cfg, FeatureRunner<CustomKeySpamConfig>& runner) {
	runner.run(cfg, [&cfg]() {
		tapKey(cfg.spamKey);
		}, "Custom Key Spam");
}
