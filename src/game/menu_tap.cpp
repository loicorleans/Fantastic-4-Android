// The game's menus are not read from what it draws yet: the touch controls drive them with the pad alone
// (native/touch.cpp's kMenuTaps is off), so these only keep the runtime's hooks satisfied.
#include "common/menu_tap.h"

namespace game {

void MenuQuad(uint32_t, float, float, float, float, float, float, float, float) {}
void MenuFrame() {}
bool CurrentMenu(MenuList&) { return false; }

}  // namespace game
