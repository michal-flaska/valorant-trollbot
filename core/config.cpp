#include "config.h"
#include "logger.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace {
	unsigned int hexToUInt(const std::string& str) {
		unsigned int value = 0;
		std::string hexStr = str;
		if (hexStr.length() >= 2 && hexStr.substr(0, 2) == "0x") {
			hexStr = hexStr.substr(2);
		}
		std::stringstream ss;
		ss << std::hex << hexStr;
		ss >> value;
		return value;
	}

	std::string trim(const std::string& str) {
		const size_t start = str.find_first_not_of(" \t\r\n");
		const size_t end = str.find_last_not_of(" \t\r\n");
		return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
	}

	std::string toLower(const std::string& str) {
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(), ::tolower);
		return result;
	}

	Constants::LogLevel parseLogLevel(const std::string& value) {
		const int level = std::stoi(value);
		if (level >= 0 && level <= 3) {
			return static_cast<Constants::LogLevel>(level);
		}
		return Constants::DEFAULT_LOG_LEVEL;
	}

	void parseFeatureSection(const std::string& section, const std::string& key,
		const std::string& value, Config& config) {
		if (section == "inspectspam") {
			if (key == "enabled") config.inspect.enabled = value == "1";
			else if (key == "mode") config.inspect.mode = value;
			else if (key == "triggerkey") config.inspect.triggerKey = hexToUInt(value);
			else if (key == "inspectkey") config.inspect.inspectKey = hexToUInt(value);
			else if (key == "startdelay") config.inspect.startDelay = std::stoul(value);
			else if (key == "repeatdelay") config.inspect.repeatDelay = std::stoul(value);
		}
		else if (section == "mouseglitch") {
			if (key == "enabled") config.mouseGlitch.enabled = value == "1";
			else if (key == "mode") config.mouseGlitch.mode = value;
			else if (key == "triggerkey") config.mouseGlitch.triggerKey = hexToUInt(value);
			else if (key == "maxdistance") config.mouseGlitch.maxDistance = std::stoi(value);
			else if (key == "startdelay") config.mouseGlitch.startDelay = std::stoul(value);
			else if (key == "repeatdelay") config.mouseGlitch.repeatDelay = std::stoul(value);
		}
		else if (section == "spinbot") {
			if (key == "enabled") config.spinbot.enabled = value == "1";
			else if (key == "mode") config.spinbot.mode = value;
			else if (key == "triggerkey") config.spinbot.triggerKey = hexToUInt(value);
			else if (key == "direction") config.spinbot.direction = value;
			else if (key == "speed") config.spinbot.speed = std::stoi(value);
			else if (key == "interval") config.spinbot.interval = std::stoi(value);
			else if (key == "startdelay") config.spinbot.startDelay = std::stoul(value);
			else if (key == "repeatdelay") config.spinbot.repeatDelay = std::stoul(value);
		}
		else if (section == "bhop") {
			if (key == "enabled") config.bhop.enabled = value == "1";
			else if (key == "mode") config.bhop.mode = value;
			else if (key == "triggerkey") config.bhop.triggerKey = hexToUInt(value);
			else if (key == "jumpkey") config.bhop.jumpKey = hexToUInt(value);
			else if (key == "startdelay") config.bhop.startDelay = std::stoul(value);
			else if (key == "repeatdelay") config.bhop.repeatDelay = std::stoul(value);
		}
		else if (section == "developer") {
			if (key == "enablelogging") config.developer.enableLogging = value == "1";
			else if (key == "loglevel") config.developer.logLevel = parseLogLevel(value);
			else if (key == "mainloopdelay") config.developer.mainLoopDelay = std::stoul(value);
			else if (key == "threadsafetychecks") config.developer.threadSafetyChecks = value == "1";
		}
	}
}

bool loadConfig(const std::string& path, Config& config) {
	std::ifstream file(path);
	if (!file.is_open()) {
		Logger::error("Cannot open config file: " + path);
		return false;
	}

	std::string line, section;
	while (std::getline(file, line)) {
		line = trim(line);
		if (line.empty() || line[0] == ';' || line[0] == '#') continue;

		if (line.front() == '[' && line.back() == ']') {
			section = toLower(line.substr(1, line.size() - 2));
			continue;
		}

		const auto eq = line.find('=');
		if (eq == std::string::npos) continue;

		std::string key = toLower(trim(line.substr(0, eq)));
		std::string value = trim(line.substr(eq + 1));

		// Remove inline comments
		const size_t commentPos = value.find(';');
		if (commentPos != std::string::npos) {
			value = trim(value.substr(0, commentPos));
		}

		parseFeatureSection(section, key, value, config);
	}

	Logger::info("Configuration loaded successfully");
	return true;
}

ConfigPtr createConfig(const std::string& path) {
	auto config = std::make_unique<Config>();
	if (!loadConfig(path, *config)) {
		return nullptr;
	}
	return config;
}
