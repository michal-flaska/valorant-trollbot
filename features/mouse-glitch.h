#pragma once
#include "../core/config.h"
#include "../core/feature-base.h"
#include <random>

class MouseGlitch {
private:
	FeatureRunner<MouseGlitchConfig> runner_;
	std::random_device rd_;
	std::mt19937 gen_;

public:
	MouseGlitch() : gen_(rd_()) {}
	void run(const MouseGlitchConfig& config);
};
