#include "component.h"
#include <SDL2/SDL.h>

void Component::draw(SDL_Renderer *ren) {
    draw(ren, 1.0);
}

void Component::draw(SDL_Renderer *ren, float scale) {
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
