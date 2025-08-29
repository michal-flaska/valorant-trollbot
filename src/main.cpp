#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include "config.h"
#include "../features/bhop.h"
#include "../features/inspect-spam.h"
#include "../features/mouse-glitch.h"
#include "../features/spinbot.h"

void welcomeMessage() {
	std::cout << "Valorant Trollbot starting...\nMake sure to edit config.ini\n--Mike\n\n";
}

int main() {
	welcomeMessage();
	Config cfg;
	if (!loadConfig("config.ini", cfg)) {
		std::cerr << "Failed to load config.ini\n";
		return 1;
	}

	bool bhopToggle = false, lastBhop = false;
	bool inspectToggle = false, lastInspect = false;
	bool glitchToggle = false, lastGlitch = false;
	bool spinToggle = false, lastSpin = false;

	for (;;) {
		runBhop(cfg.bhop, bhopToggle, lastBhop);
		runInspect(cfg.inspect, inspectToggle, lastInspect);
		runMouseGlitch(cfg.mouseGlitch, glitchToggle, lastGlitch);
		runSpinbot(cfg.spinbot, spinToggle, lastSpin);
		Sleep(1);
	}
}
