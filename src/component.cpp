#include "component.h"
#include <SDL2/SDL.h>

void Component::draw(SDL_Renderer *ren) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dst;
    dst.x = position.x;
    dst.y = position.y;
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
