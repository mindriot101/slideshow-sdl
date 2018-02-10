#ifndef CHANGE_COLOUR_H_
#define CHANGE_COLOUR_H_

#include <cstdint>
#include <SDL2/SDL.h>

struct ChangeColour {
    ChangeColour(SDL_Renderer *ren, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    ChangeColour(SDL_Renderer *ren, const SDL_Color &colour);
    ~ChangeColour();

    SDL_Renderer *ren = nullptr;
    SDL_Color current;
};

#endif //  CHANGE_COLOUR_H_
