#ifndef DEF_H
#define DEF_H
#define BACKGROUND_IMG "img\\forest.jpg"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr const char* WINDOW_TITLE = "Hello World!";

constexpr const char* BIRD_SPRITE_FILE = "img\\83127-sprite-area-line-animated-bird-film.png";
constexpr float COLLISION_THRESHOLD = 50.0f;

// Mảng clip của chim
constexpr int BIRD_CLIPS[][4] = {
    {0, 0, 182, 168},
    {181, 0, 182, 168},
    {364, 0, 182, 168},
    {547, 0, 182, 168},
    {728, 0, 182, 168},

    {0, 170, 182, 168},
    {181, 170, 182, 168},
    {364, 170, 182, 168},
    {547, 170, 182, 168},
    {728, 170, 182, 168},

    {0, 340, 182, 168},
    {181, 340, 182, 168},
    {364, 340, 182, 168},
    {547, 340, 182, 168},
};
constexpr int BIRD_FRAMES = sizeof(BIRD_CLIPS) / sizeof(BIRD_CLIPS[0]);

#endif // DEF_H
