#include "component.h"
#include <SDL2/SDL.h>
#include "change_colour.h"

void Component::fill(SDL_Renderer *ren) {
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = 1280;
    dst.h = 720;
    SDL_RenderCopy(ren, texture, NULL, &dst);
}

void Component::draw(SDL_Renderer *ren) {
    draw(ren, 1.0);
}

void Component::draw(SDL_Renderer *ren, float scale) {
    switch (component_type) {
        case ComponentType::Text:
        case ComponentType::Image:
            {
                int w, h;
                SDL_QueryTexture(texture, NULL, NULL, &w, &h);

                w *= scale;
                h *= scale;

                SDL_Rect dst;
                dst.x = position.x - w / 2;
                dst.y = position.y - h / 2;
                dst.w = w;
                dst.h = h;
                SDL_RenderCopy(ren, texture, NULL, &dst);
            }
            break;
        case ComponentType::Rect:
            {
                ChangeColour _c(ren, rect_colour.r, rect_colour.g, rect_colour.g, 255);
                SDL_RenderFillRect(ren, &rect_box);
            }
            break;
    }
}

std::shared_ptr<Component> Component::text_component() {
    auto component = std::make_shared<Component>();
    component->component_type = ComponentType::Text;
    return component;
}

std::shared_ptr<Component> Component::image_component() {
    auto component = std::make_shared<Component>();
    component->component_type = ComponentType::Image;
    return component;
}

std::shared_ptr<Component> Component::rect_component(
        const SDL_Rect &rect,
        const SDL_Color &colour) {
    auto component = std::make_shared<Component>();
    component->component_type = ComponentType::Rect;
    component->rect_box = rect;
    component->rect_colour.r = colour.r;
    component->rect_colour.g = colour.g;
    component->rect_colour.b = colour.b;
    component->rect_colour.a = colour.a;
    component->scale = Option<float>::None();
    return component;
}
