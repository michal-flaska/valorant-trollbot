#pragma once
#include <string>

struct FeatureConfig {
	bool enabled = false;
	std::string mode;       // "hold" or "toggle"
	unsigned int triggerKey = 0;
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
	int interval = 10;              // milliseconds
};

struct BhopConfig : FeatureConfig {
	unsigned int jumpKey = 0;
	int startDelay = 0;  // ms before starting to press jump
	int repeatDelay = 25;
};

struct Config {
	InspectConfig inspect;
	MouseGlitchConfig mouseGlitch;
	SpinbotConfig spinbot;
	BhopConfig bhop;
};

bool loadConfig(const std::string& path, Config& cfg);
