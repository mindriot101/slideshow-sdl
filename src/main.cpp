#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

int main() {
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;
    bool error_occurred = false;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL_Init error: " << SDL_GetError() << endl;
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

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }

        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
    }

    return 0;
}
