#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include "config.h"
#include "../features/bhop.h"
#include "../features/inspect-spam.h"
#include "../features/mouse-glitch.h"
#include "../features/spinbot.h"

void welcomeMessage() {
	std::cout << "Valorant Trollbot starting..."
		  << '\n' << "Make sure to edit config.ini"
		  << '\n' << "--Mike" << '\n' << '\n';
}

std::atomic<bool> running(true);

void bhopThread(const BhopConfig& cfg) {
	bool toggle = false, lastPressed = false;
	while (running) {
		runBhop(cfg, toggle, lastPressed);
		Sleep(cfg.repeatDelay > 0 ? cfg.repeatDelay : 25);
	}
}

void inspectThread(const InspectConfig& cfg) {
	bool toggle = false, lastPressed = false;
	while (running) {
		runInspect(cfg, toggle, lastPressed);
		Sleep(cfg.repeatDelay > 0 ? cfg.repeatDelay : 100);
	}
}

void glitchThread(const MouseGlitchConfig& cfg) {
	bool toggle = false, lastPressed = false;
	while (running) {
		runMouseGlitch(cfg, toggle, lastPressed);
		Sleep(cfg.repeatDelay > 0 ? cfg.repeatDelay : 50);
	}
}

void spinThread(const SpinbotConfig& cfg) {
	bool toggle = false, lastPressed = false;
	while (running) {
		runSpinbot(cfg, toggle, lastPressed);
		Sleep(cfg.interval > 0 ? cfg.interval : 15);
	}
}

int main() {
	welcomeMessage();
	Config cfg;
	if (!loadConfig("config.ini", cfg)) {
		std::cerr << "Failed to load config.ini" << '\n';
		system("pause");
		return 1;
	}

	std::cout << "Features loaded:\n";
	if (cfg.bhop.enabled) std::cout << "- Bhop enabled (trigger: 0x" << std::hex << cfg.bhop.triggerKey << ", jump: 0x" << cfg.bhop.jumpKey << std::dec << ")\n";
	if (cfg.inspect.enabled) std::cout << "- Inspect spam enabled (trigger: 0x" << std::hex << cfg.inspect.triggerKey << ", inspect: 0x" << cfg.inspect.inspectKey << std::dec << ")\n";
	if (cfg.mouseGlitch.enabled) std::cout << "- Mouse glitch enabled (trigger: 0x" << std::hex << cfg.mouseGlitch.triggerKey << std::dec << ")\n";
	if (cfg.spinbot.enabled) std::cout << "- Spinbot enabled (trigger: 0x" << std::hex << cfg.spinbot.triggerKey << std::dec << ")\n";
	std::cout << '\n' << "Press ESC to exit" << '\n' << '\n';

	// Start threads for each enabled feature
	std::vector<std::thread> threads;

	if (cfg.bhop.enabled) {
		threads.push_back(std::thread(bhopThread, std::ref(cfg.bhop)));
	}
	if (cfg.inspect.enabled) {
		threads.push_back(std::thread(inspectThread, std::ref(cfg.inspect)));
	}
	if (cfg.mouseGlitch.enabled) {
		threads.push_back(std::thread(glitchThread, std::ref(cfg.mouseGlitch)));
	}
	if (cfg.spinbot.enabled) {
		threads.push_back(std::thread(spinThread, std::ref(cfg.spinbot)));
	}

	// Main loop - check for exit key
	while (running) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			running = false;
			std::cout << "Shutting down..." << '\n';
			break;
		}
		Sleep(50);
	}

	// Wait for all threads to finish
	for (size_t i = 0; i < threads.size(); ++i) {
		if (threads[i].joinable()) threads[i].join();
	}

	return 0;
}
