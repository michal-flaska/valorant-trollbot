#include "logger.h"

bool Logger::enabled_ = Constants::DEFAULT_LOGGING;
Constants::LogLevel Logger::level_ = Constants::DEFAULT_LOG_LEVEL;
