// Fantastic Four (original Xbox). Hooks of the game's own code go here: [[hook]] entries in config/game.toml and
// X86_FUNC replacements of recompiled functions. None yet: start without any and add them as the log asks for them.
#include <cstring>

#include "common/aspect.h"
#include "common/options.h"

namespace game {

// the languages the settings panel offers; which of them the disc has is not checked yet
bool LanguageAvailable(const std::string& code) { return KnownLanguage(code); }

// no HUD hook to tell play from a menu: the touch controls stay up
bool HudShown() { return true; }

}  // namespace game

namespace app {

// the console's XC_LANGUAGE the game reads at boot, from the language setting as this run started
uint32_t ConsoleLanguage() {
    const std::string& l = game::BootLanguage();
    if (l == "deu") return 3;
    if (l == "fra") return 4;
    if (l == "esp") return 5;
    if (l == "ita") return 6;
    return 1;  // English
}

}  // namespace app
