#include <iostream>
#include <thread>
#include <chrono>
#include "config.h"
#include "input.h"
#include "../features/bhop.h"
#include "../features/spinbot.h"
#include "../features/inspect-spam.h"
#include "../features/mouse-glitch.h"

int main() {
	std::cout << "Valorant Trollbot starting..." << std::endl;

	Config cfg;
	if (!loadConfig("config.ini", cfg)) {
		std::cerr << "Failed to load config.ini! Make sure the file exists in /config." << std::endl;
		return 1;
	}

	std::cout << "Config loaded. Launching features..." << std::endl;

	// Start all features
	if (cfg.bhop.enabled) startBhop(cfg.bhop);
	if (cfg.spinbot.enabled) startSpinbot(cfg.spinbot);
	if (cfg.inspect.enabled) startInspectSpam(cfg.inspect);
	if (cfg.mouseGlitch.enabled) startMouseGlitch(cfg.mouseGlitch);

	std::cout << "All features running. Press Ctrl+C to exit." << std::endl;

	// Keep main thread alive indefinitely
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}
