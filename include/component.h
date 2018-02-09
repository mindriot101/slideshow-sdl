#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SDL2/SDL_rect.h>
#include "component_type.h"

struct SDL_Texture;
struct SDL_Renderer;

struct Component {
    ComponentType component_type;
    SDL_Point position;
    SDL_Texture *texture;

    void draw(SDL_Renderer *ren);
};

#endif // COMPONENT_H_
