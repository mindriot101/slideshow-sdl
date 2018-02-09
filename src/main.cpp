#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "slide.h"
#include "component.h"
#include "image_manager.h"
#include "slideshow.h"
#include "font_manager.h"

using namespace std;

struct App {
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;
    unique_ptr<ImageManager> image_manager;
    unique_ptr<FontManager> font_manager;
    unique_ptr<Slideshow> show;

    int init();
    int run();
};

int App::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL_Init error: " << SDL_GetError() << endl;
        return 1;
    }

    if (TTF_Init() != 0) {
        cerr << "TTF_Init error: " << SDL_GetError() << endl;
        return 1;
    }

    win = SDL_CreateWindow("Hello world", 0, 0, 1280, 720, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        cerr << "SDL_CreateWindow error: " << SDL_GetError() << endl;
        return 1;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        cerr << "SDL_CreateRenderer error: " << SDL_GetError() << endl;
        return 1;
    }

    image_manager = make_unique<ImageManager>(ren);
    font_manager = make_unique<FontManager>(ren);

    image_manager->add("cat", "../run_tree/images/cat.png");
    font_manager->add("droid", "../run_tree/fonts/DroidSansMono.ttf", 84);

    show = make_unique<Slideshow>();

    {
        auto current = make_shared<Slide>();

        auto image_component = Component::image_component();
        image_component->texture = image_manager->get("cat");
        if (image_component->texture == nullptr) {
            fprintf(stderr, "TEXTURE IS NULL!!!\n");
            return 1;
        }
        image_component->component_type = ComponentType::Image;
        image_component->position = {1280 / 2, 720 / 2};
        current->add(image_component);


        auto text_texture = font_manager->create_text("Hello world", "droid", {255, 255, 0, 255});

        auto text_component = Component::text_component();
        text_component->texture = text_texture;
        text_component->component_type = ComponentType::Text;
        text_component->position = {1280 / 2, 720 / 2};
        current->add(text_component);

        show->append(current);
    }

    return 0;
}

int App::run() {
    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                    case SDLK_n:
                        show->next_slide();
                        break;
                    case SDLK_BACKSPACE:
                    case SDLK_p:
                        show->previous_slide();
                        break;
                    case SDLK_f:
                        show->toggle_fullscreen(win);
                        break;
                }
            }
        }

        SDL_RenderClear(ren);
        show->draw(ren);
        SDL_RenderPresent(ren);
    }

    return 0;
}

int main() {
    App app;
    if (app.init()) {
        return 1;
    }

    return app.run();
}
