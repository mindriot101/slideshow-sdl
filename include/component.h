#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <memory>
#include <SDL2/SDL_rect.h>
#include "component_type.h"

struct SDL_Texture;
struct SDL_Renderer;

struct Component {
    ComponentType component_type;
    SDL_Point position;
    SDL_Texture *texture;

    void draw(SDL_Renderer *ren);

    static std::shared_ptr<Component> text_component();
    static std::shared_ptr<Component> image_component();
};

#endif // COMPONENT_H_
