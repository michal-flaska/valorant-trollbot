#pragma once
#include <string>
#include <vector>

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
};

struct CustomKeySpamConfig : FeatureConfig {
	unsigned int spamKey = 0;
};

struct VoiceChatSpamConfig : FeatureConfig {
	unsigned int voiceKey = 0;
};

struct InteractSpamConfig : FeatureConfig {
	unsigned int interactKey = 0;
};

struct ChatSpammerConfig : FeatureConfig {
	unsigned int chatKey = 0x0D;
	std::string messageFile = "messages.txt";
	std::string messageOrder = "sequential";
	std::string chatTarget = "team";
	bool restoreClipboard = true;
};

struct DevConfig {
	bool showToggleLogs = true;
	bool showStartupInfo = true;
	unsigned int mainLoopDelay = 50;
	unsigned int threadLoopDelay = 10;
	unsigned int exitKey = 0x1B;
};

struct Config {
	InspectConfig inspect;
	BhopConfig bhop;
	WeaponCyclerConfig weaponCycler;
	CustomKeySpamConfig customKeySpam;
	VoiceChatSpamConfig voiceChatSpam;
	InteractSpamConfig interactSpam;
	ChatSpammerConfig chatSpammer;
	DevConfig dev;
};

bool loadConfig(const std::string& path, Config& cfg);
bool loadMessages(const std::string& path, std::vector<std::string>& messages);
