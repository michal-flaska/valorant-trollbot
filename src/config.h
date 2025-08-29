#pragma once
#include <string>

struct FeatureConfig {
	bool enabled = false;
	std::string mode;       // "hold" or "toggle"
	unsigned int triggerKey = 0;
	unsigned int startDelay = 0;   // ms before starting action
	unsigned int repeatDelay = 25; // ms between actions
};

struct InspectConfig : FeatureConfig {
	unsigned int inspectKey = 0;
};

struct MouseGlitchConfig : FeatureConfig {
	int maxDistance = 10;
};

struct SpinbotConfig : FeatureConfig {
	std::string direction = "right"; // left/right
	int speed = 20;
	int interval = 10;              // ms per mouse move
};

struct BhopConfig : FeatureConfig {
	unsigned int jumpKey = 0;
};

struct Config {
	InspectConfig inspect;
	MouseGlitchConfig mouseGlitch;
	SpinbotConfig spinbot;
	BhopConfig bhop;
};

bool loadConfig(const std::string& path, Config& cfg);
