#ifndef SLIDESHOW_H_
#define SLIDESHOW_H_

#include <cstdint>
#include <vector>
#include <memory>

struct Slide;
struct SDL_Window;
struct SDL_Renderer;

struct Slideshow {
    std::vector<std::shared_ptr<Slide>> slides;
    uint32_t current_slide = 0;
    bool fullscreen = false;

    void append(std::shared_ptr<Slide> &slide);
    void draw(SDL_Renderer *ren);
    void next_slide();
    void previous_slide();
    void toggle_fullscreen(SDL_Window *window);
};

#endif //  SLIDESHOW_H_
