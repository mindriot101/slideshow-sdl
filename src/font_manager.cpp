#include "font_manager.h"

FontManager::FontManager(SDL_Renderer *ren) : ren(ren) {}

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

SDL_Texture *FontManager::create_text(const std::string &text, const std::string font_tag, SDL_Color color) const {
    auto font = get(font_tag);

    auto surf = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surf == nullptr) {
        fprintf(stderr, "Error creating surface for text: %s\n", text.c_str());
        return nullptr;
    }

    auto texture = SDL_CreateTextureFromSurface(ren, surf);
    if (texture == nullptr) {
        fprintf(stderr, "Error creating text texture for text: %s\n", text.c_str());
        return nullptr;
    }

    SDL_FreeSurface(surf);
    return texture;
}
