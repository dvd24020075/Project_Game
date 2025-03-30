#include "score_effect.h"

ScoreEffect::ScoreEffect(float _x, float _y)
    : x(_x), y(_y), startTime(SDL_GetTicks()) {
    color.r = 128 + rand() % 128;
    color.g = 128 + rand() % 128;
    color.b = 128 + rand() % 128;
    color.a = 255;
}

void ScoreEffect::update() {
    y -= 0.5f;
}


