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

		std::string msg;
		if (cfg.messageOrder == "random") {
			std::uniform_int_distribution<size_t> dist(0, messages.size() - 1);
			msg = messages[dist(gen)];
		}
		else {
			msg = messages[currentIndex];
			currentIndex = (currentIndex + 1) % messages.size();
		}

		// Prepend chat command
		std::string prefix = (cfg.chatTarget == "all") ? "/all " : "/team ";
		return prefix + msg;
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

		saveOriginalClipboard(cfg);

		if (!setClipboardText(message)) {
			std::cerr << "Failed to set clipboard text\n";
			return;
		}

		// Open chat (just Enter - command will handle routing)
		tapKey(cfg.chatKey);
		Sleep(75);

		// Paste and send
		pasteFromClipboard();
		Sleep(50);
		tapKey(VK_RETURN);

		if (cfg.restoreClipboard) {
			Sleep(25);
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
