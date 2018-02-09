#include "image_manager.h"

ImageManager::ImageManager(SDL_Renderer *ren) : ren(ren) {}

void ImageManager::add(const std::string &tag, const std::string &path) {
    auto texture = IMG_LoadTexture(ren, path.c_str());
    if (texture == nullptr) {
        fprintf(stderr, "Error loading texture: %s\n", path.c_str());
    }

    images[tag] = texture;
}

SDL_Texture *ImageManager::get(const std::string &tag) {
    return images.at(tag);
}
