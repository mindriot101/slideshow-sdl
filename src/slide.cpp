#include "slide.h"
#include "component.h"
#include "SDL2/SDL.h"

Slide::~Slide() {
    for (auto component: components) {
        if (component != nullptr) {
            delete component;
        }
    }
}

void Slide::add(Component *component) {
    this->components.push_back(component);
}

void Slide::draw(SDL_Renderer *ren) {
    for (auto component: components) {
        component->draw(ren);
    }
}
