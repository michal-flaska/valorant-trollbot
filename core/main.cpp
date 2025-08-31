#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include "config.h"
#include "../features/bhop.h"
#include "../features/inspect-spam.h"
#include "../features/mouse-glitch.h"
#include "../features/spinbot.h"

void printWelcome() {
	std::cout << "Valorant Trollbot starting..."
		<< '\n' << "Make sure to edit config.ini"
		<< '\n' << "--Mike" << '\n' << '\n';
}

void printLoadedFeatures(const Config& cfg) {
	std::cout << "Features loaded:\n";
	if (cfg.bhop.enabled)
		std::cout << "- Bhop (" << cfg.bhop.mode << " mode, trigger: 0x" << std::hex << cfg.bhop.triggerKey
		<< ", jump: 0x" << cfg.bhop.jumpKey << std::dec << ")\n";
	if (cfg.inspect.enabled)
		std::cout << "- Inspect spam (" << cfg.inspect.mode << " mode, trigger: 0x" << std::hex << cfg.inspect.triggerKey
		<< ", inspect: 0x" << cfg.inspect.inspectKey << std::dec << ")\n";
	if (cfg.mouseGlitch.enabled)
		std::cout << "- Mouse glitch (" << cfg.mouseGlitch.mode << " mode, trigger: 0x" << std::hex << cfg.mouseGlitch.triggerKey
		<< std::dec << ")\n";
	if (cfg.spinbot.enabled)
		std::cout << "- Spinbot (" << cfg.spinbot.mode << " mode, trigger: 0x" << std::hex << cfg.spinbot.triggerKey
		<< std::dec << ")\n";
	std::cout << '\n' << "Press ESC to exit" << '\n' << '\n';
}

std::atomic<bool> running{ true };

void bhopThread(const BhopConfig& cfg) {
	FeatureRunner<BhopConfig> runner;
	while (running.load(std::memory_order_relaxed)) {
		runBhop(cfg, runner);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void inspectThread(const InspectConfig& cfg) {
	FeatureRunner<InspectConfig> runner;
	while (running.load(std::memory_order_relaxed)) {
		runInspect(cfg, runner);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void mouseGlitchThread(const MouseGlitchConfig& cfg) {
	FeatureRunner<MouseGlitchConfig> runner;
	while (running.load(std::memory_order_relaxed)) {
		runMouseGlitch(cfg, runner);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void spinbotThread(const SpinbotConfig& cfg) {
	FeatureRunner<SpinbotConfig> runner;
	while (running.load(std::memory_order_relaxed)) {
		runSpinbot(cfg, runner);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main() {
	printWelcome();

	Config cfg;
	if (!loadConfig("config.ini", cfg)) {
		std::cerr << "Failed to load config.ini" << '\n';
		system("pause");
		return 1;
	}

	printLoadedFeatures(cfg);

	std::vector<std::thread> threads;

	if (cfg.bhop.enabled) {
		threads.emplace_back(bhopThread, cfg.bhop);
	}
	if (cfg.inspect.enabled) {
		threads.emplace_back(inspectThread, cfg.inspect);
	}
	if (cfg.mouseGlitch.enabled) {
		threads.emplace_back(mouseGlitchThread, cfg.mouseGlitch);
	}
	if (cfg.spinbot.enabled) {
		threads.emplace_back(spinbotThread, cfg.spinbot);
	}

	while (running.load(std::memory_order_relaxed)) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			running.store(false, std::memory_order_relaxed);
			std::cout << "Shutting down..." << '\n';
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}

	return 0;
}
