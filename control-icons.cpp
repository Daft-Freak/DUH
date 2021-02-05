#include "control-icons.hpp"
#include "assets.hpp"

#include "graphics/sprite.hpp"

using namespace blit;

namespace duh {

  static Surface *buttons_8 = nullptr, *buttons_12 = nullptr, *buttons_16 = nullptr;

  static Surface *get_sprites(int size) {
    if(size <= 8) {
      if(!buttons_8)
        buttons_8 = Surface::load(asset_buttons_8);

      return buttons_8;
    }
    
    if(size <= 12) {
      if(!buttons_12)
        buttons_12 = Surface::load(asset_buttons_12);

      return buttons_12;
    }
    
    if(size <= 16) {
      if(!buttons_16)
        buttons_16 = Surface::load(asset_buttons_16);

      return buttons_16;
    }
    return nullptr;
  }

  void draw_control_icon(Surface *surf, Icon icon, Point pos, int size, Pen fg, Pen bg) {
    const uint8_t sprite_indices[] {
      0, 0, 0, 0, //ABXY
      2, // Home
      3, // Menu
      4, // Stick
      7, 7, // Stick UD/LR
      5, 5, 5, 5, // Stick directions
      6, 6, // DPad UD/LR
      1, 1, 1, 1 // DPad directions
    };

    const uint8_t sprite_transforms[] {
      R90, R180, NONE, R270,
      NONE,
      NONE,
      NONE,
      NONE, R90,
      R270, NONE, R180, R90,
      NONE, R90,
      R270, NONE, R180, R90
    };

    auto sprites = get_sprites(size);
    if(!sprites)
      return;
  
    int sprite_index = sprite_indices[static_cast<int>(icon)];
    int transform = sprite_transforms[static_cast<int>(icon)];

    int size_tiles = (size + 7) / 8;
    auto sprite_rect = Rect(sprite_index * size_tiles, 0, size_tiles, size_tiles);

    // fixup transformed 12px icons
    if(size == 12 && (transform & SpriteTransform::HORIZONTAL))
      pos.x -= 4;

    if(size == 12 && (transform & SpriteTransform::VERTICAL))
      pos.y -= 4;

    sprites->palette[1] = fg;
    sprites->palette[2] = bg;

    auto old_sprites = surf->sprites;
    surf->sprites = sprites;
    surf->sprite(sprite_rect, pos, transform);
    surf->sprites = old_sprites;
  }
}