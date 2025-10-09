#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include "config.h"
#include "../features/bhop.h"
#include "../features/inspect-spam.h"
#include "../features/weapon-cycler.h"
#include "../features/custom-key-spam.h"
#include "../features/voice-chat-spam.h"
#include "../features/interact-spam.h"
#include "../features/chat-spammer.h"

DevConfig g_devConfig;

void printWelcome() {
	if (g_devConfig.showStartupInfo) {
		std::cout << "Valorant Trollbot starting..."
			<< '\n' << "Make sure to edit config.ini"
			<< '\n' << "--Mike" << '\n' << '\n';
	}
}

void printLoadedFeatures(const Config& cfg) {
	if (g_devConfig.showStartupInfo) {
		std::cout << "Features loaded:\n";
		if (cfg.bhop.enabled)
			std::cout << "- Bhop (" << cfg.bhop.mode << " mode, trigger: 0x" << std::hex << cfg.bhop.triggerKey
			<< ", jump: 0x" << cfg.bhop.jumpKey << std::dec << ")\n";
		if (cfg.inspect.enabled)
			std::cout << "- Inspect spam (" << cfg.inspect.mode << " mode, trigger: 0x" << std::hex << cfg.inspect.triggerKey
			<< ", inspect: 0x" << cfg.inspect.inspectKey << std::dec << ")\n";
		if (cfg.weaponCycler.enabled)
			std::cout << "- Weapon Cycler (" << cfg.weaponCycler.mode << " mode, trigger: 0x" << std::hex << cfg.weaponCycler.triggerKey
			<< std::dec << ")\n";
		if (cfg.customKeySpam.enabled)
			std::cout << "- Custom Key Spam (" << cfg.customKeySpam.mode << " mode, trigger: 0x" << std::hex << cfg.customKeySpam.triggerKey
			<< ", spam: 0x" << cfg.customKeySpam.spamKey << std::dec << ")\n";
		if (cfg.voiceChatSpam.enabled)
			std::cout << "- Voice Chat Spam (" << cfg.voiceChatSpam.mode << " mode, trigger: 0x" << std::hex << cfg.voiceChatSpam.triggerKey
			<< ", voice: 0x" << cfg.voiceChatSpam.voiceKey << std::dec << ")\n";
		if (cfg.interactSpam.enabled)
			std::cout << "- Interact Spam (" << cfg.interactSpam.mode << " mode, trigger: 0x" << std::hex << cfg.interactSpam.triggerKey
			<< ", interact: 0x" << cfg.interactSpam.interactKey << std::dec << ")\n";
		if (cfg.chatSpammer.enabled)
			std::cout << "- Chat Spammer (" << cfg.chatSpammer.mode << " mode, trigger: 0x" << std::hex << cfg.chatSpammer.triggerKey
			<< ", file: " << cfg.chatSpammer.messageFile << std::dec << ")\n";
		std::cout << '\n' << "Press ESC to exit" << '\n';
		std::cout << "Press Numpad 0 to disable all active features" << '\n' << '\n';
	}
}

std::atomic<bool> running{ true };
std::atomic<bool> disableAllRequested{ false };

FeatureRunner<BhopConfig> bhopRunner;
FeatureRunner<InspectConfig> inspectRunner;
FeatureRunner<WeaponCyclerConfig> weaponCyclerRunner;
FeatureRunner<CustomKeySpamConfig> customKeySpamRunner;
FeatureRunner<VoiceChatSpamConfig> voiceChatSpamRunner;
FeatureRunner<InteractSpamConfig> interactSpamRunner;
FeatureRunner<ChatSpammerConfig> chatSpammerRunner;

void bhopThread(const BhopConfig& cfg) {
	while (running.load(std::memory_order_relaxed)) {
		if (disableAllRequested.load(std::memory_order_relaxed)) {
			bhopRunner.reset("Bhop");
		}
		runBhop(cfg, bhopRunner);
		std::this_thread::sleep_for(std::chrono::milliseconds(g_devConfig.threadLoopDelay));
	}
}

void inspectThread(const InspectConfig& cfg) {
	while (running.load(std::memory_order_relaxed)) {
		if (disableAllRequested.load(std::memory_order_relaxed)) {
			inspectRunner.reset("Inspect Spam");
		}
		runInspect(cfg, inspectRunner);
		std::this_thread::sleep_for(std::chrono::milliseconds(g_devConfig.threadLoopDelay));
	}
}

void weaponCyclerThread(const WeaponCyclerConfig& cfg) {
	while (running.load(std::memory_order_relaxed)) {
		if (disableAllRequested.load(std::memory_order_relaxed)) {
			weaponCyclerRunner.reset("Weapon Cycler");
		}
		runWeaponCycler(cfg, weaponCyclerRunner);
		std::this_thread::sleep_for(std::chrono::milliseconds(g_devConfig.threadLoopDelay));
	}
}

void customKeySpamThread(const CustomKeySpamConfig& cfg) {
	while (running.load(std::memory_order_relaxed)) {
		if (disableAllRequested.load(std::memory_order_relaxed)) {
			customKeySpamRunner.reset("Custom Key Spam");
		}
		runCustomKeySpam(cfg, customKeySpamRunner);
		std::this_thread::sleep_for(std::chrono::milliseconds(g_devConfig.threadLoopDelay));
	}
}

void voiceChatSpamThread(const VoiceChatSpamConfig& cfg) {
	while (running.load(std::memory_order_relaxed)) {
		if (disableAllRequested.load(std::memory_order_relaxed)) {
			voiceChatSpamRunner.reset("Voice Chat Spam");
		}
		runVoiceChatSpam(cfg, voiceChatSpamRunner);
		std::this_thread::sleep_for(std::chrono::milliseconds(g_devConfig.threadLoopDelay));
	}
}

void interactSpamThread(const InteractSpamConfig& cfg) {
	while (running.load(std::memory_order_relaxed)) {
		if (disableAllRequested.load(std::memory_order_relaxed)) {
			interactSpamRunner.reset("Interact Spam");
		}
		runInteractSpam(cfg, interactSpamRunner);
		std::this_thread::sleep_for(std::chrono::milliseconds(g_devConfig.threadLoopDelay));
	}
}

void chatSpammerThread(const ChatSpammerConfig& cfg) {
	while (running.load(std::memory_order_relaxed)) {
		if (disableAllRequested.load(std::memory_order_relaxed)) {
			chatSpammerRunner.reset("Chat Spammer");
		}
		runChatSpammer(cfg, chatSpammerRunner);
		std::this_thread::sleep_for(std::chrono::milliseconds(g_devConfig.threadLoopDelay));
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

	g_devConfig = cfg.dev;

	printLoadedFeatures(cfg);

	std::vector<std::thread> threads;

	if (cfg.bhop.enabled) {
		threads.emplace_back(bhopThread, cfg.bhop);
	}
	if (cfg.inspect.enabled) {
		threads.emplace_back(inspectThread, cfg.inspect);
	}
	if (cfg.weaponCycler.enabled) {
		threads.emplace_back(weaponCyclerThread, cfg.weaponCycler);
	}
	if (cfg.customKeySpam.enabled) {
		threads.emplace_back(customKeySpamThread, cfg.customKeySpam);
	}
	if (cfg.voiceChatSpam.enabled) {
		threads.emplace_back(voiceChatSpamThread, cfg.voiceChatSpam);
	}
	if (cfg.interactSpam.enabled) {
		threads.emplace_back(interactSpamThread, cfg.interactSpam);
	}
	if (cfg.chatSpammer.enabled) {
		threads.emplace_back(chatSpammerThread, cfg.chatSpammer);
	}

	bool lastDisableAllPressed = false;

	while (running.load(std::memory_order_relaxed)) {
		if (GetAsyncKeyState(g_devConfig.exitKey) & 0x8000) {
			running.store(false, std::memory_order_relaxed);
			if (g_devConfig.showStartupInfo) {
				std::cout << "Shutting down..." << '\n';
			}
			break;
		}

		bool disableAllPressed = GetAsyncKeyState(g_devConfig.disableAllKey) & 0x8000;
		if (disableAllPressed && !lastDisableAllPressed) {
			disableAllRequested.store(true, std::memory_order_relaxed);
			if (g_devConfig.showToggleLogs) {
				std::cout << "Disabling all active features..." << '\n';
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			disableAllRequested.store(false, std::memory_order_relaxed);
		}
		lastDisableAllPressed = disableAllPressed;

		std::this_thread::sleep_for(std::chrono::milliseconds(g_devConfig.mainLoopDelay));
	}

	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}

	return 0;
}
