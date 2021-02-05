#include <cstdint>

#include "32blit.hpp"
#include "graphics/color.hpp" 

#include "control-icons.hpp"

using namespace blit;

void init() {
  set_screen_mode(ScreenMode::hires);
}

void update(uint32_t time_ms) {

}

void render(uint32_t time_ms) {

  // all the icons
  int x = 8, y = 8;
  for(int i = 0; i <= static_cast<int>(duh::Icon::DPadR); i++) {
    duh::draw_control_icon(&screen, static_cast<duh::Icon>(i), Point(x, y), 8);
    x += 10;
  }

  y += 10;

  // now draw all the sizes with many colours
  for(int s = 8; s <= 16; s += 4) {
    x = 8;
    for(int i = 0; i <= static_cast<int>(duh::Icon::DPadR); i++) {
      float h = i / 20.0f + time_ms / 1000.0f;
      h = h - std::floor(h);
      auto fg = hsv_to_rgba(h, 1.0f, 0.8f);
      auto bg = hsv_to_rgba(h, 0.4f, 0.3f);
      duh::draw_control_icon(&screen, static_cast<duh::Icon>(i), Point(x, y), s, fg, bg);
      x += s + 2;
    }
    y += s + 2;
  }
}