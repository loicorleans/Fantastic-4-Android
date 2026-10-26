// Button prompts are not detected for this game: no tappable prompts, no icon boxes.
#include "common/menu_tap.h"

namespace game {

void PromptQuad(uint32_t, float, float, float, float, float, float, float, float) {}
void PromptFrame() {}
bool CurrentPrompts(std::vector<Prompt>&) { return false; }
void CurrentIcons(std::vector<Prompt>&) {}

}  // namespace game
