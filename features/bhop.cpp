#include "bhop.h"
#include "../core/input.h"

void Bhop::run(const BhopConfig& config) {
	runner_.run(config, [&config]() {
		tapKey(config.jumpKey);
		});
}
