#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_

#include <string>
#include <map>
#include <SDL2/SDL_ttf.h>

struct FontManager {
    FontManager(SDL_Renderer *ren);
    void add(const std::string &tag, const std::string &path, int font_size);
    TTF_Font *get(const std::string &tag) const;
    SDL_Texture *create_text(const std::string &text, const std::string font_tag, SDL_Color color) const;

    std::map<std::string, TTF_Font *> fonts;
    SDL_Renderer *ren;
};

#endif // FONT_MANAGER_H_
