#pragma once
#include "../core/config.h"
#include "../core/feature-base.h"

class InspectSpam {
private:
	FeatureRunner<InspectConfig> runner_;

public:
	void run(const InspectConfig& config);
};
