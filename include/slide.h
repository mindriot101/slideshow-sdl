#ifndef SLIDE_H_
#define SLIDE_H_

#include <vector>
struct Component;
struct SDL_Renderer;

struct Slide {
    std::vector<Component *> components;

    void draw(SDL_Renderer *ren);
    void add(Component *component);
    ~Slide();
};

#endif //  SLIDE_H_
