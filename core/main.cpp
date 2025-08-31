#include <windows.h>
#include <iostream>
#include "config.h"
#include "logger.h"
#include "constants.h"
#include "thread-manager.h"
#include "../features/bhop.h"
#include "../features/inspect-spam.h"
#include "../features/mouse-glitch.h"
#include "../features/spinbot.h"

namespace {
	void showWelcome() {
		std::cout << "Valorant Trollbot starting...\n"
			<< "Make sure to edit config.ini\n"
			<< "--Mike\n\n";
	}

	void showFeatureStatus(const Config& config) {
		Logger::info("Features loaded:");
		if (config.bhop.enabled) {
			Logger::info("- Bhop enabled (trigger: 0x" + std::to_string(config.bhop.triggerKey) +
				", jump: 0x" + std::to_string(config.bhop.jumpKey) + ")");
		}
		if (config.inspect.enabled) {
			Logger::info("- Inspect spam enabled (trigger: 0x" + std::to_string(config.inspect.triggerKey) +
				", inspect: 0x" + std::to_string(config.inspect.inspectKey) + ")");
		}
		if (config.mouseGlitch.enabled) {
			Logger::info("- Mouse glitch enabled (trigger: 0x" + std::to_string(config.mouseGlitch.triggerKey) + ")");
		}
		if (config.spinbot.enabled) {
			Logger::info("- Spinbot enabled (trigger: 0x" + std::to_string(config.spinbot.triggerKey) + ")");
		}
		Logger::info("Press ESC to exit\n");
	}
}

int main() {
	showWelcome();

	const auto config = createConfig("config.ini");
	if (!config) {
		std::cerr << "Failed to load config.ini\n";
		system("pause");
		return 1;
	}

	Logger::initialize(config->developer.enableLogging, config->developer.logLevel);

	showFeatureStatus(*config);

	ThreadManager threadManager;

	// Create feature instances
	auto bhop = std::make_unique<Bhop>();
	auto inspect = std::make_unique<InspectSpam>();
	auto mouseGlitch = std::make_unique<MouseGlitch>();
	auto spinbot = std::make_unique<Spinbot>();

	// Start feature threads
	if (config->bhop.enabled) {
		threadManager.addThread([&bhop, &config, &threadManager]() {
			while (threadManager.isRunning()) {
				bhop->run(config->bhop);
				Sleep(config->bhop.repeatDelay);
			}
			});
	}

	if (config->inspect.enabled) {
		threadManager.addThread([&inspect, &config, &threadManager]() {
			while (threadManager.isRunning()) {
				inspect->run(config->inspect);
				Sleep(config->inspect.repeatDelay);
			}
			});
	}

	if (config->mouseGlitch.enabled) {
		threadManager.addThread([&mouseGlitch, &config, &threadManager]() {
			while (threadManager.isRunning()) {
				mouseGlitch->run(config->mouseGlitch);
				Sleep(config->mouseGlitch.repeatDelay);
			}
			});
	}

	if (config->spinbot.enabled) {
		threadManager.addThread([&spinbot, &config, &threadManager]() {
			while (threadManager.isRunning()) {
				spinbot->run(config->spinbot);
				Sleep(config->spinbot.interval);
			}
			});
	}

	// Main loop
	while (threadManager.isRunning()) {
		if (GetAsyncKeyState(Constants::VK_ESCAPE_KEY) & 0x8000) {
			Logger::info("Shutting down...");
			threadManager.stop();
			break;
		}
		Sleep(config->developer.mainLoopDelay);
	}

	return 0;
}
