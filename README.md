# Valorant Trollbot

> [!IMPORTANT]
> This is a learning project for C++ and Win32 API development. Don't be an idiot and use this in ranked games - it's meant for custom lobbies and messing around with friends. Riot will ban you if you use cheats in competitive matches, so keep it to practice range or custom games only.

## Known Issues
> [!CAUTION]
> **Chat Spammer - ALL Chat Not Working**<br />
> The chat spammer currently only sends messages to team chat, even when `ChatTarget=all` is configured. The SHIFT+ENTER combination for all chat isn't being recognized properly by Valorant. Multiple input methods have been attempted but the issue persists. Contributions welcome!

## What is this?

A simple Windows app I built to learn more about:
- Win32 keyboard/mouse input simulation with `SendInput`
- INI config file parsing
- Multi-threaded C++ applications
- Modular code structure

Originally made for Valorant but also works on CS2 and probably other games too.

## Features

**Working features:**
- **Bhop** - Auto jump spam while holding a key
- **Inspect Spam** - Rapidly inspect your weapon
- **Custom Key Spam** - Spam any key you want (like W for movement)
- **Voice Chat Spam** - Rapidly toggle voice chat on/off while your beautiful voice is talkin' shit
- **Interact Spam** - Spam the interact key (useful for spamming defuse/plant)
- **Weapon Cycler** - Automatically cycle through your weapons
- **Chat Spammer** - Send random messages from your list (currently in development)

**Broken features (thanks Vanguard):**
- ~~Mouse Glitch~~ - Vanguard blocks software mouse movement
- ~~Spinbot~~ - Same issue, mouse movement is detected and blocked

Each feature supports hold/toggle modes, custom keybinds, and timing configuration.

## Setup

1. Download or clone this repo
2. Open `valorant-trollbot.sln` in Visual Studio 2022
3. Build for x64 (Debug or Release, doesn't matter)
4. Edit `config.ini` to set your keybinds
5. Run the executable

Make sure `config.ini` is in the same folder as the .exe file.

## Configuration

Edit `config.ini` to customize everything. The hex codes for keys can be found [here](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes).

bhop example:
```ini
[Bhop]
Enabled=1
Mode=hold
TriggerKey=0x06 ; MB 5
JumpKey=0x20    ; SPACEBAR
StartDelay=500
RepeatDelay=15
```

All delays are in milliseconds. Set `Enabled=0` to disable features you don't want.

## Usage

Launch the exe after setting up your config. Press your trigger keys to activate features. Toggle mode stays on until you press the key again, hold mode only works while the key is pressed.

Press ESC to exit.

## Notes

- The mouse movement features don't work in Valorant because Vanguard detects and blocks them. Keyboard inputs work fine though.
- This should work on CS2 and other games without kernel-level anti-cheat
- Only tested on Windows 10/11
- Built this mainly to understand how input simulation works in Windows

Don't blame me if you get banned for being dumb with it.
