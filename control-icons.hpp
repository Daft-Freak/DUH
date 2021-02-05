#pragma once
#include "graphics/surface.hpp"
#include "types/point.hpp"

namespace duh {
  enum class Icon {
    A = 0,
    B,
    X,
    Y,
    Home,
    Menu,

    StickPress,
    StickLR,
    StickUD,
    StickL,
    StickU,
    StickD,
    StickR,

    DPadLR,
    DPadUD,
    DPadL,
    DPadU,
    DPadD,
    DPadR
  };

  void draw_control_icon(blit::Surface *surf, Icon icon, blit::Point pos, int size = 12, blit::Pen fg = blit::Pen(0xFF, 0xFF, 0xFF), blit::Pen bg = blit::Pen(0x50, 0x64, 0x78));
}