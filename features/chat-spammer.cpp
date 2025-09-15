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

		// Open chat
		tapKey(cfg.chatKey);
		Sleep(50);  // Small delay to ensure chat opens

		// Paste message
		pasteFromClipboard();
		Sleep(25);  // Small delay before sending

		// Send message
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
