#include "inspect-spam.h"
#include "../core/input.h"
#include "../core/feature-base.h"

void runInspect(const InspectConfig& cfg, bool& toggle, bool& lastPressed) {
	runFeature(cfg, toggle, lastPressed, [&cfg]() {
		tapKey(cfg.inspectKey);
		});
}
