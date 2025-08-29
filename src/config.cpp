#include "config.h"
#include <fstream>
#include <sstream>
#include <algorithm>

static unsigned int hexToUInt(const std::string& s) {
	unsigned int x = 0;
	std::stringstream ss;
	// Remove 0x prefix if present
	std::string hexStr = s;
	if (hexStr.length() >= 2 && hexStr.substr(0, 2) == "0x") {
		hexStr = hexStr.substr(2);
	}
	ss << std::hex << hexStr;
	ss >> x;
	return x;
}

static std::string trim(const std::string& str) {
	size_t start = str.find_first_not_of(" \t\r\n");
	size_t end = str.find_last_not_of(" \t\r\n");
	return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

static std::string toLower(const std::string& str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

bool loadConfig(const std::string& path, Config& cfg) {
	std::ifstream file(path);
	if (!file.is_open()) return false;

	std::string line, section;

	while (std::getline(file, line)) {
		line = trim(line);
		if (line.empty() || line[0] == ';' || line[0] == '#') continue;

		if (line.front() == '[' && line.back() == ']') {
			section = toLower(line.substr(1, line.size() - 2));
			continue;
		}

		auto eq = line.find('=');
		if (eq == std::string::npos) continue;

		std::string key = toLower(trim(line.substr(0, eq)));
		std::string val = trim(line.substr(eq + 1));

		// Remove comments from value
		size_t commentPos = val.find(';');
		if (commentPos != std::string::npos) {
			val = trim(val.substr(0, commentPos));
		}

		if (section == "inspectspam") {
			if (key == "enabled") cfg.inspect.enabled = val == "1";
			else if (key == "mode") cfg.inspect.mode = val;
			else if (key == "triggerkey") cfg.inspect.triggerKey = hexToUInt(val);
			else if (key == "inspectkey") cfg.inspect.inspectKey = hexToUInt(val);
			else if (key == "startdelay") cfg.inspect.startDelay = std::stoul(val);
			else if (key == "repeatdelay") cfg.inspect.repeatDelay = std::stoul(val);
		}
		else if (section == "mouseglitch") {
			if (key == "enabled") cfg.mouseGlitch.enabled = val == "1";
			else if (key == "mode") cfg.mouseGlitch.mode = val;
			else if (key == "triggerkey") cfg.mouseGlitch.triggerKey = hexToUInt(val);
			else if (key == "maxdistance") cfg.mouseGlitch.maxDistance = std::stoi(val);
			else if (key == "startdelay") cfg.mouseGlitch.startDelay = std::stoul(val);
			else if (key == "repeatdelay") cfg.mouseGlitch.repeatDelay = std::stoul(val);
		}
		else if (section == "spinbot") {
			if (key == "enabled") cfg.spinbot.enabled = val == "1";
			else if (key == "mode") cfg.spinbot.mode = val;
			else if (key == "triggerkey") cfg.spinbot.triggerKey = hexToUInt(val);
			else if (key == "direction") cfg.spinbot.direction = val;
			else if (key == "speed") cfg.spinbot.speed = std::stoi(val);
			else if (key == "interval") cfg.spinbot.interval = std::stoi(val);
			else if (key == "startdelay") cfg.spinbot.startDelay = std::stoul(val);
			else if (key == "repeatdelay") cfg.spinbot.repeatDelay = std::stoul(val);
		}
		else if (section == "bhop") {
			if (key == "enabled") cfg.bhop.enabled = val == "1";
			else if (key == "mode") cfg.bhop.mode = val;
			else if (key == "triggerkey") cfg.bhop.triggerKey = hexToUInt(val);
			else if (key == "jumpkey") cfg.bhop.jumpKey = hexToUInt(val);
			else if (key == "startdelay") cfg.bhop.startDelay = std::stoul(val);
			else if (key == "repeatdelay") cfg.bhop.repeatDelay = std::stoul(val);
		}
	}

	return true;
}
