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

struct WeaponCyclerConfig : FeatureConfig {
	unsigned int primaryKey = 0x31;
	unsigned int secondaryKey = 0x32;
	unsigned int knifeKey = 0x33;
	unsigned int spikeKey = 0x34;
	bool usePrimary = true;
	bool useSecondary = true;
	bool useKnife = true;
	bool useSpike = false;
	unsigned int interval = 100;
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
	WeaponCyclerConfig weaponCycler;
	DevConfig dev;
};

bool loadConfig(const std::string& path, Config& cfg);
