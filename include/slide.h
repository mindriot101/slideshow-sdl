#ifndef SLIDE_H_
#define SLIDE_H_

#include <vector>
#include <memory>

struct Component;
struct SDL_Renderer;

struct Slide {
    std::vector<std::shared_ptr<Component>> components;

    void draw(SDL_Renderer *ren);
    void add(std::shared_ptr<Component> &component);
};

#endif //  SLIDE_H_
