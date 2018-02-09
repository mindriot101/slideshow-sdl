#include "slideshow.h"
#include "slide.h"
#include <SDL2/SDL.h>

void Slideshow::append(std::shared_ptr<Slide> &slide) {
    slides.push_back(slide);
}

void Slideshow::draw(SDL_Renderer *ren) {
    auto slide = slides.at(current_slide);
    slide->draw(ren);
}

void Slideshow::next_slide() {
    if ((current_slide + 1) < slides.size()) {
        current_slide += 1;
    }
}

void Slideshow::previous_slide() {
    if (current_slide > 0) {
        current_slide -= 1;
    }
}

void Slideshow::toggle_fullscreen(SDL_Window *window) {
    fullscreen = !fullscreen;
    SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}
