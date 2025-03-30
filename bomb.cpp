#include "bomb.h"

Bomb::Bomb(float _x, float _y, SDL_Texture* _texture)
    : x(_x), y(_y), speed(2.0f), acceleration(0.3f), texture(_texture) {}

void Bomb::update() {
    y += speed;
    speed += acceleration;
}

void Bomb::render(SDL_Renderer* renderer) const {
    SDL_Rect dest = { static_cast<int>(x), static_cast<int>(y), 64, 64 };
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

