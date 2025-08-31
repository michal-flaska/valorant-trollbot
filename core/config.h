#pragma once
#include "constants.h"
#include <string>
#include <memory>

struct FeatureConfig {
	bool enabled = false;
	std::string mode = "hold";
	unsigned int triggerKey = 0;
	unsigned int startDelay = 0;
	unsigned int repeatDelay = Constants::DEFAULT_FEATURE_DELAY;
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

struct DeveloperConfig {
	bool enableLogging = Constants::DEFAULT_LOGGING;
	Constants::LogLevel logLevel = Constants::DEFAULT_LOG_LEVEL;
	unsigned int mainLoopDelay = Constants::DEFAULT_MAIN_LOOP_DELAY;
	bool threadSafetyChecks = Constants::DEFAULT_THREAD_SAFETY_CHECKS;
};

struct Config {
	InspectConfig inspect;
	MouseGlitchConfig mouseGlitch;
	SpinbotConfig spinbot;
	BhopConfig bhop;
	DeveloperConfig developer;
};

using ConfigPtr = std::unique_ptr<Config>;

bool loadConfig(const std::string& path, Config& config);
ConfigPtr createConfig(const std::string& path);
