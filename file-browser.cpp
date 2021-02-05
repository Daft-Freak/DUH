#include "file-browser.hpp"

#include "control-icons.hpp"

#include "engine/engine.hpp"

using namespace blit;

namespace duh {

  FileBrowser::FileBrowser(const Font &font) : Menu("", nullptr, 0, font) {
    // too early
    //files = list_files("");

    item_h = font.char_h + 2;
    item_adjust_y = 0;

    header_h = item_h;
    footer_h = 0;
    margin_y = 0;

    background_colour = Pen(0x11, 0x11, 0x11);
    foreground_colour = Pen(0xF7, 0xF7, 0xF7);
    selected_item_background = Pen(0x22, 0x22, 0x22);
  }

  void FileBrowser::init() {
    update_list();
  }

  void FileBrowser::render() {
    Menu::render();

    const int iconSize = font.char_h > 8 ? 12 : 8;

    const int32_t backTextWidth = screen.measure_text("Back", font).w;

    Rect r(display_rect.tl(), Size(display_rect.w, header_h));

    screen.pen = header_foreground;

    r.x += item_padding_x;
    r.w -= item_padding_x * 2;
    r.h += font.spacing_y;

    // back icon
    if(!cur_dir.empty()) {
      Point iconOffset(-(backTextWidth + iconSize + 2), 1); // from the top-right

      screen.text("Back", font, r, true, TextAlign::center_right);
      draw_control_icon(&screen, Icon::B, r.tr() + iconOffset, iconSize, header_foreground);
    }
  }

  void FileBrowser::set_extensions(std::set<std::string> exts) {
    file_exts = exts;
  }

  void FileBrowser::set_on_file_open(void (*func)(std::string)) {
    on_file_open = func;
  }

  void FileBrowser::set_current_dir(const std::string &dir) {
    if(dir[0] != '/')
      cur_dir = "/" + dir;
    else
      cur_dir = dir;

    if(cur_dir.back() != '/')
      cur_dir += "/";

    update_list();
  }

  void FileBrowser::update_list() {
    title = cur_dir;

    files = list_files(cur_dir.substr(0, cur_dir.length() - 1));

    std::sort(files.begin(), files.end(), [](FileInfo &a, FileInfo & b){return a.name < b.name;});

    if(!file_exts.empty()) {
      // filter by extensions
      files.erase(std::remove_if(files.begin(), files.end(), [this](const FileInfo &f) {
        if(f.name[0] == '.')
          return true;

        if(!(f.flags & FileFlags::directory)) {
          std::string ext;
          auto dotPos = f.name.find_last_of('.');
          if(dotPos != std::string::npos)
            ext = f.name.substr(dotPos);

          // convert to lower case
          std::for_each(ext.begin(), ext.end(), [](char & c) {c = tolower(c);});

          if(file_exts.find(ext) == file_exts.end())
            return true;
        }

        return false;
      }), files.end());
    }

    // update menu items
    file_items.resize(files.size());

    unsigned int i = 0;
    for(auto &file : files) {
      if(file.flags & FileFlags::directory)
        file.name += "/";

      file_items[i].id = i;
      file_items[i++].label = file.name.c_str();
    }

    set_items(file_items.data(), file_items.size());
  }

  void FileBrowser::render_item(const Item &item, int y, int index) const {
    Menu::render_item(item, y, index);

    if(index == current_item) {
      const int iconSize = font.char_h > 8 ? 12 : 8;

      Rect r(display_rect.x + item_padding_x, y, display_rect.w - item_padding_x * 2 - iconSize - 2, item_h);
      Point iconPos = Point(display_rect.x + display_rect.w - item_padding_x -iconSize, y + 1); // from the top-right
      draw_control_icon(&screen, Icon::A, iconPos, iconSize, foreground_colour);
    }
  }

  void FileBrowser::update_item(const Item &item) {
    if(buttons.released & Button::B) {
      if(cur_dir != "/") {
        // go up
        auto pos = cur_dir.find_last_of('/', cur_dir.length() - 2);
        if(pos == std::string::npos)
          cur_dir = "";
        else
          cur_dir = cur_dir.substr(0, pos + 1);

        update_list();
      }
    }
  }

  void FileBrowser::item_activated(const Item &item){
    if(!num_items)
      return;

    if(files[current_item].flags & FileFlags::directory) {
      cur_dir += files[current_item].name;
      update_list();
    }
    else if(on_file_open)
      on_file_open(cur_dir + files[current_item].name);
  }
}