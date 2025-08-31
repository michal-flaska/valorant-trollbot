#pragma once

namespace Constants {
	// Default delays (milliseconds)
	constexpr unsigned int DEFAULT_MAIN_LOOP_DELAY = 50;
	constexpr unsigned int DEFAULT_FEATURE_DELAY = 25;
	constexpr unsigned int MIN_DELAY = 1;
	constexpr unsigned int MAX_DELAY = 5000;

	// Key codes
	constexpr unsigned int VK_ESCAPE_KEY = 0x1B;

	// Log levels
	enum class LogLevel {
		NONE = 0,
		ERROR = 1,
		INFO = 2,
		DEBUG = 3
	};

	// Default config values
	constexpr bool DEFAULT_LOGGING = true;
	constexpr LogLevel DEFAULT_LOG_LEVEL = LogLevel::INFO;
	constexpr bool DEFAULT_THREAD_SAFETY_CHECKS = false;
}
