#include "change_colour.h"

ChangeColour::ChangeColour(SDL_Renderer *ren, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_GetRenderDrawColor(ren, &current.r, &current.g, &current.b, &current.a);
    SDL_SetRenderDrawColor(ren, r, g, b, a);
    this->ren = ren;
}

ChangeColour::ChangeColour(SDL_Renderer *ren, const SDL_Color &colour) {
    ChangeColour(ren, colour.r, colour.g, colour.b, colour.a);
}

ChangeColour::~ChangeColour() {
    SDL_SetRenderDrawColor(ren, current.r, current.g, current.b, current.a);
}
