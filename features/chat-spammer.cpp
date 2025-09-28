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
			// For ALL chat: SHIFT + ENTER (held together)
			INPUT inputs[4] = {};

			// Shift down
			inputs[0].type = INPUT_KEYBOARD;
			inputs[0].ki.wVk = VK_SHIFT;
			inputs[0].ki.dwFlags = 0;

			// Enter down (while shift is held)
			inputs[1].type = INPUT_KEYBOARD;
			inputs[1].ki.wVk = static_cast<WORD>(cfg.chatKey);
			inputs[1].ki.dwFlags = 0;

			// Enter up
			inputs[2].type = INPUT_KEYBOARD;
			inputs[2].ki.wVk = static_cast<WORD>(cfg.chatKey);
			inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

			// Shift up
			inputs[3].type = INPUT_KEYBOARD;
			inputs[3].ki.wVk = VK_SHIFT;
			inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

			SendInput(4, inputs, sizeof(INPUT));
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
