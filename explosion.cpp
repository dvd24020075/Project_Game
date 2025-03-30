#include "explosion.h"
#include <cstdlib>
#include <cmath>

Explosion::Explosion(float _x, float _y, SDL_Texture* _texture)
    : x(_x), y(_y), texture(_texture), frame(0) {
    for (int i = 0; i < 10; i++) {
        float angle = (rand() % 360) * M_PI / 180.0;
        float radius = (rand() % 30) + 20;
        particles.push_back({ x + radius * cos(angle), y + radius * sin(angle) });
    }
}

bool Explosion::update() {
    frame++;
    return frame >= maxFrames;
}

void Explosion::render(SDL_Renderer* renderer) const {
    SDL_Rect srcRect = { frame * 128, 0, 128, 128 };
    for (const auto& p : particles) {
        SDL_Rect destRect = { static_cast<int>(p.first), static_cast<int>(p.second), 64, 64 };
        int alpha = 255 - (frame * 40);
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    }
}

