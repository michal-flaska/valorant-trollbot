#include "chat-spammer.h"
#include "../core/input.h"
#include <vector>
#include <random>
#include <iostream>

namespace {
	std::vector<std::string> messages;
	bool initialized = false;
	size_t currentIndex = 0;
	std::string originalClipboard;
	bool clipboardSaved = false;

	std::random_device rd;
	std::mt19937 gen(rd());

	void initializeMessages(const ChatSpammerConfig& cfg) {
		if (!loadMessages(cfg.messageFile, messages)) {
			std::cerr << "Failed to load messages from: " << cfg.messageFile << '\n';
			messages.clear();
			messages.push_back("Default message - edit " + cfg.messageFile);
		}

		currentIndex = 0;
		initialized = true;

		if (g_devConfig.showStartupInfo) {
			std::cout << "Chat Spammer loaded " << messages.size() << " messages from " << cfg.messageFile << '\n';
			std::cout << "Chat Target: " << cfg.chatTarget << '\n';
		}
	}

	std::string getNextMessage(const ChatSpammerConfig& cfg) {
		if (messages.empty()) return "";

		if (cfg.messageOrder == "random") {
			std::uniform_int_distribution<size_t> dist(0, messages.size() - 1);
			return messages[dist(gen)];
		}
		else {
			// Sequential
			std::string msg = messages[currentIndex];
			currentIndex = (currentIndex + 1) % messages.size();
			return msg;
		}
	}

	void saveOriginalClipboard(const ChatSpammerConfig& cfg) {
		if (cfg.restoreClipboard && !clipboardSaved) {
			originalClipboard = getClipboardText();
			clipboardSaved = true;
		}
	}

	void restoreOriginalClipboard(const ChatSpammerConfig& cfg) {
		if (cfg.restoreClipboard && clipboardSaved) {
			setClipboardText(originalClipboard);
			clipboardSaved = false;
		}
	}

	void openChat(const ChatSpammerConfig& cfg) {
		if (cfg.chatTarget == "all") {
			// For ALL chat: Hold SHIFT, press ENTER, release both
			// First: Hold SHIFT down
			INPUT shiftDown = {};
			shiftDown.type = INPUT_KEYBOARD;
			shiftDown.ki.wVk = VK_SHIFT;
			shiftDown.ki.dwFlags = 0;
			SendInput(1, &shiftDown, sizeof(INPUT));

			Sleep(10); // Small delay to ensure shift is registered

			// Then: Press and release ENTER while SHIFT is held
			tapKey(cfg.chatKey);

			Sleep(10); // Small delay before releasing shift

			// Finally: Release SHIFT
			INPUT shiftUp = {};
			shiftUp.type = INPUT_KEYBOARD;
			shiftUp.ki.wVk = VK_SHIFT;
			shiftUp.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &shiftUp, sizeof(INPUT));
		}
		else {
			// For TEAM chat: just ENTER
			tapKey(cfg.chatKey);
		}
	}

	void sendMessage(const ChatSpammerConfig& cfg) {
		std::string message = getNextMessage(cfg);
		if (message.empty()) return;

		// Save original clipboard if needed
		saveOriginalClipboard(cfg);

		// Copy message to clipboard
		if (!setClipboardText(message)) {
			std::cerr << "Failed to set clipboard text\n";
			return;
		}

		// Open appropriate chat (team or all)
		openChat(cfg);
		Sleep(75);  // Increased delay to ensure chat opens properly

		// Paste message
		pasteFromClipboard();
		Sleep(50);  // Delay before sending

		// Send message (always just Enter for sending)
		tapKey(VK_RETURN);

		// Restore clipboard if configured
		if (cfg.restoreClipboard) {
			Sleep(25);  // Small delay before restoring
			restoreOriginalClipboard(cfg);
		}
	}
}

void runChatSpammer(const ChatSpammerConfig& cfg, FeatureRunner<ChatSpammerConfig>& runner) {
	if (!initialized) {
		initializeMessages(cfg);
	}

	runner.run(cfg, [&cfg]() {
		sendMessage(cfg);
		}, "Chat Spammer");
}
