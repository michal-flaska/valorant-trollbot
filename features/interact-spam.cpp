#include "interact-spam.h"
#include "../core/input.h"

void runInteractSpam(const InteractSpamConfig& cfg, FeatureRunner<InteractSpamConfig>& runner) {
	runner.run(cfg, [&cfg]() {
		tapKey(cfg.interactKey);
		}, "Interact Spam");
}
