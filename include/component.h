#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <memory>
#include <SDL2/SDL_rect.h>
#include "component_type.h"
#include "optional.h"

struct SDL_Texture;
struct SDL_Renderer;

struct Component {
    ComponentType component_type;
    SDL_Point position;
    SDL_Texture *texture;
    Option<float> scale = Option<float>::None();
    bool fit_width = false;
    bool fit = false;

    /* Rect components */
    SDL_Rect rect_box;
    SDL_Color rect_colour;

    void fill(SDL_Renderer *ren);
    void draw(SDL_Renderer *ren);
    void draw(SDL_Renderer *ren, float scale);

    static std::shared_ptr<Component> text_component();
    static std::shared_ptr<Component> image_component();
    static std::shared_ptr<Component> rect_component(
            const SDL_Rect &rect,
            const SDL_Color &colour
            );
};

#endif // COMPONENT_H_
