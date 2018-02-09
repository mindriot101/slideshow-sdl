#include "slide.h"
#include "component.h"
#include "SDL2/SDL.h"

void Slide::add(std::shared_ptr<Component> &component) {
    this->components.push_back(component);
}

void Slide::draw(SDL_Renderer *ren) {
    for (auto component: components) {
        if (component->scale) {
            component->draw(ren, component->scale.val());
        } else {
            component->draw(ren);
        }
    }
}
