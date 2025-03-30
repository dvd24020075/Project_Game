#ifndef BOMB_H
#define BOMB_H

#include <SDL.h>

struct Bomb {
    float x, y;
    float speed;
    float acceleration;
    SDL_Texture* texture;

    // Khai báo hàm tạo (constructor)
    Bomb(float _x, float _y, SDL_Texture* _texture);

    // Khai báo các hàm thành viên
    void update();
    void render(SDL_Renderer* renderer) const;
};

#endif // BOMB_H

