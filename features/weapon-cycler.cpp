#include "weapon-cycler.h"
#include "../core/input.h"
#include <vector>

static std::vector<unsigned int> weaponKeys;
static bool initialized = false;
static size_t currentIndex = 0;

void runWeaponCycler(const WeaponCyclerConfig& cfg, FeatureRunner<WeaponCyclerConfig>& runner) {
	if (!initialized) {
		weaponKeys.clear();
		weaponKeys.reserve(4);

		if (cfg.usePrimary) weaponKeys.push_back(cfg.primaryKey);
		if (cfg.useSecondary) weaponKeys.push_back(cfg.secondaryKey);
		if (cfg.useKnife) weaponKeys.push_back(cfg.knifeKey);
		if (cfg.useSpike) weaponKeys.push_back(cfg.spikeKey);

		initialized = true;
		currentIndex = 0;
	}

	runner.run(cfg, []() {
		if (!weaponKeys.empty()) {
			tapKey(weaponKeys[currentIndex]);
			currentIndex = (currentIndex + 1) % weaponKeys.size();
		}
		}, "Weapon Cycler");
}
