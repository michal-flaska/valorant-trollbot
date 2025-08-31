#pragma once
#include "../core/config.h"
#include "../core/feature-base.h"

class Bhop {
private:
	FeatureRunner<BhopConfig> runner_;

public:
	void run(const BhopConfig& config);
};
