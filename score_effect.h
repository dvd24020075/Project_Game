#ifndef SCORE_EFFECT_H
#define SCORE_EFFECT_H

#include <SDL.h>
#include <cstdlib>

struct ScoreEffect {
    float x, y;
    Uint32 startTime;
    SDL_Color color;

    ScoreEffect(float _x, float _y);
    void update();
};

#endif // SCORE_EFFECT_H

