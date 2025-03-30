#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SDL.h>
#include <vector>
#include <utility>

struct Explosion {
    float x, y;
    SDL_Texture* texture;
    int frame;
    static const int maxFrames = 6;
    std::vector<std::pair<float, float>> particles;

    Explosion(float _x, float _y, SDL_Texture* _texture);
    bool update();
    void render(SDL_Renderer* renderer) const;
};

#endif // EXPLOSION_H

