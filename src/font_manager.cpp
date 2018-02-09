#include "font_manager.h"

void FontManager::add(const std::string &tag, const std::string &path, int font_size) {
    auto font = TTF_OpenFont(path.c_str(), font_size);
    if (font == nullptr) {
        fprintf(stderr, "Failure loading font %s\n", path.c_str());
        return;
    }

    fonts[tag] = font;
}

TTF_Font *FontManager::get(const std::string &tag) const {
    return fonts.at(tag);
}
