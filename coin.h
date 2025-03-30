#ifndef COIN_H
#define COIN_H

#include <SDL.h>

struct Coin {
    float x, y;
    SDL_Texture* texture;
    Uint32 spawnTime;

    Coin(float _x, float _y, SDL_Texture* _texture);
    void render(SDL_Renderer* renderer) const;
};

#endif // COIN_H

