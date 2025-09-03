#include "voice-chat-spam.h"
#include "../core/input.h"

void runVoiceChatSpam(const VoiceChatSpamConfig& cfg, FeatureRunner<VoiceChatSpamConfig>& runner) {
	runner.run(cfg, [&cfg]() {
		tapKey(cfg.voiceKey);
		}, "Voice Chat Spam");
}
