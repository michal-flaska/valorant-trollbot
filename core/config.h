#pragma once
#include <string>

struct FeatureConfig {
	bool enabled = false;
	std::string mode = "hold";
	unsigned int triggerKey = 0;
	unsigned int startDelay = 0;
	unsigned int repeatDelay = 50;
};

struct InspectConfig : FeatureConfig {
	unsigned int inspectKey = 0;
};

struct MouseGlitchConfig : FeatureConfig {
	int maxDistance = 10;
};

struct SpinbotConfig : FeatureConfig {
	std::string direction = "right";
	int speed = 20;
	int interval = 15;
};

struct BhopConfig : FeatureConfig {
	unsigned int jumpKey = 0;
};

struct DevConfig {
	bool showToggleLogs = true;
	bool showStartupInfo = true;
	unsigned int mainLoopDelay = 50;
	unsigned int threadLoopDelay = 10;
	unsigned int exitKey = 0x1B;
	int mouseMethod = 0;
};

struct Config {
	InspectConfig inspect;
	MouseGlitchConfig mouseGlitch;
	SpinbotConfig spinbot;
	BhopConfig bhop;
	DevConfig dev;
};

bool loadConfig(const std::string& path, Config& cfg);
