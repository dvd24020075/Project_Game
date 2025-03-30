#include "coin.h"
#include <SDL.h>

Coin::Coin(float _x, float _y, SDL_Texture* _texture)
    : x(_x), y(_y), texture(_texture), spawnTime(SDL_GetTicks()) {}

void Coin::render(SDL_Renderer* renderer) const {
    SDL_Rect dest = { static_cast<int>(x), static_cast<int>(y), 32, 32 };
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

