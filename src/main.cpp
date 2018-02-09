#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "slide.h"
#include "component.h"
#include "slideshow.h"

using namespace std;

SDL_Texture *load_texture(const string &file, SDL_Renderer *ren) {
    auto texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) {
        cerr << "Error loading texture: " << file << endl;
        return nullptr;
    }
    return texture;
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    render_texture(tex, ren, x, y, w, h);
}

SDL_Texture *create_text(const string &message, const string &font_file,
                SDL_Color color, int fontSize, SDL_Renderer *ren) {
    auto font = TTF_OpenFont(font_file.c_str(), fontSize);
    if (font == nullptr) {
        cerr << "Error loading font: " << font_file << ": " << SDL_GetError() << endl;
        return nullptr;
    }

    auto surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surf == nullptr) {
        cerr << "Error rendering text" << endl;
        return nullptr;
    }

    auto texture = SDL_CreateTextureFromSurface(ren, surf);
    if (texture == nullptr) {
        cerr << "Error creating text texture" << endl;
        return nullptr;
    }

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

int main() {
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;

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

    auto texture = load_texture("../run_tree/images/cat.png", ren);
    if (texture == nullptr) {
        cerr << "Error loading texture from file" << endl;
        return 1;
    }

    Slideshow show;

    {
        auto current = make_shared<Slide>();

        auto image_component = Component::image_component();
        image_component->texture = texture;
        image_component->component_type = ComponentType::Image;
        image_component->position = {800, 300};
        current->add(image_component);


        auto text_texture = create_text("Hello world", "../run_tree/fonts/DroidSansMono.ttf", {255, 255, 255, 255}, 64, ren);

        auto text_component = Component::text_component();
        text_component->texture = text_texture;
        text_component->component_type = ComponentType::Text;
        text_component->position = {200, 0};
        current->add(text_component);

        show.append(current);
    }
    {
        auto current = make_shared<Slide>();

        auto image_component = Component::image_component();
        image_component->texture = texture;
        image_component->component_type = ComponentType::Image;
        image_component->position = {800, 0};
        current->add(image_component);


        auto text_texture = create_text("Hello world", "../run_tree/fonts/DroidSansMono.ttf", {255, 255, 255, 255}, 64, ren);

        auto text_component = Component::text_component();
        text_component->texture = text_texture;
        text_component->component_type = ComponentType::Text;
        text_component->position = {0, 0};
        current->add(text_component);

        show.append(current);
    }

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                    case SDLK_n:
                        show.next_slide();
                        break;
                    case SDLK_BACKSPACE:
                    case SDLK_p:
                        show.previous_slide();
                        break;
                }
            }
        }

        SDL_RenderClear(ren);
        show.draw(ren);
        SDL_RenderPresent(ren);
    }

    return 0;
}
