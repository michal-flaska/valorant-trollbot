#include "weapon-cycler.h"
#include "../core/input.h"
#include <vector>

namespace {
	std::vector<unsigned int> weaponKeys;
	bool initialized = false;
	size_t currentIndex = 0;

	void initializeWeaponKeys(const WeaponCyclerConfig& cfg) {
		weaponKeys.clear();
		weaponKeys.reserve(4);

		if (cfg.usePrimary) weaponKeys.push_back(cfg.primaryKey);
		if (cfg.useSecondary) weaponKeys.push_back(cfg.secondaryKey);
		if (cfg.useKnife) weaponKeys.push_back(cfg.knifeKey);
		if (cfg.useSpike) weaponKeys.push_back(cfg.spikeKey);

		currentIndex = 0;
		initialized = true;
	}

	void cycleWeapon() {
		if (!weaponKeys.empty()) {
			tapKey(weaponKeys[currentIndex]);
			currentIndex = (currentIndex + 1) % weaponKeys.size();
		}
	}
}

void runWeaponCycler(const WeaponCyclerConfig& cfg, FeatureRunner<WeaponCyclerConfig>& runner) {
	if (!initialized) {
		initializeWeaponKeys(cfg);
	}

	runner.run(cfg, cycleWeapon, "Weapon Cycler");
}
