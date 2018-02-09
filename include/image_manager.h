#ifndef IMAGE_MANAGER_H_
#define IMAGE_MANAGER_H_

#include <string>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

struct SDL_Renderer;
struct SDL_Texture;

struct ImageManager {
    ImageManager(SDL_Renderer *ren);
    void add(const std::string &tag, const std::string &path);
    SDL_Texture *get(const std::string &tag);

    SDL_Renderer *ren;
    std::map<std::string, SDL_Texture*> images;
};

#endif //  IMAGE_MANAGER_H_
