#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_

#include <string>
#include <map>
#include <SDL2/SDL_ttf.h>

struct FontManager {
    void add(const std::string &tag, const std::string &path, int font_size);
    TTF_Font *get(const std::string &tag) const;

    std::map<std::string, TTF_Font *> fonts;
};

#endif // FONT_MANAGER_H_
