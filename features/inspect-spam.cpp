#include "inspect-spam.h"
#include "../core/input.h"

void InspectSpam::run(const InspectConfig& config) {
	runner_.run(config, [&config]() {
		tapKey(config.inspectKey);
		});
}
