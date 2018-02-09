#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "slide.h"
#include "component.h"

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
    bool error_occurred = false;

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

    Slide current;

    Component *image_component = new Component;
    image_component->texture = texture;
    image_component->component_type = ComponentType::Image;
    image_component->position = {800, 0};
    current.add(image_component);


    auto text_texture = create_text("Hello world", "../run_tree/fonts/DroidSansMono.ttf", {255, 255, 255, 255}, 64, ren);

    Component *text_component = new Component;
    text_component->texture = text_texture;
    text_component->component_type = ComponentType::Text;
    text_component->position = {0, 0};
    current.add(text_component);

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
                }
            }
        }

        SDL_RenderClear(ren);
        current.draw(ren);
        /* render_texture(texture, ren, 800, 0); */
        /* render_texture(text_texture, ren, 0, 0); */
        SDL_RenderPresent(ren);
    }

    return 0;
}
