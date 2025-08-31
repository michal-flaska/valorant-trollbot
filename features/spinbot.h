#pragma once
#include "../core/config.h"
#include "../core/feature-base.h"

class Spinbot {
private:
	FeatureRunner<SpinbotConfig> runner_;

public:
	void run(const SpinbotConfig& config);
};
