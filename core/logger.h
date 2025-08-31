#pragma once
#include "constants.h"
#include <iostream>
#include <string>

class Logger {
private:
	static bool enabled_;
	static Constants::LogLevel level_;

public:
	static void initialize(bool enabled, Constants::LogLevel level) {
		enabled_ = enabled;
		level_ = level;
	}

	static void error(const std::string& message) {
		if (enabled_ && level_ >= Constants::LogLevel::ERROR) {
			std::cout << "[ERROR] " << message << '\n';
		}
	}

	static void info(const std::string& message) {
		if (enabled_ && level_ >= Constants::LogLevel::INFO) {
			std::cout << "[INFO] " << message << '\n';
		}
	}

	static void debug(const std::string& message) {
		if (enabled_ && level_ >= Constants::LogLevel::DEBUG) {
			std::cout << "[DEBUG] " << message << '\n';
		}
	}
};
