#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>  // Thư viện SDL_mixer
#include "graphics.h"
#include "def.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graphics graphics;
    graphics.init();

    //  Khởi tạo SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << endl;
        return -1;
    }

    //  Tải nhạc nền (PHÁT LIÊN TỤC)
    Mix_Music *gMusic = graphics.loadMusic("assets/RunningAway.mp3");
    if (!gMusic) {
        cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
    } else {
        Mix_PlayMusic(gMusic, -1);  // 🔄 Phát nhạc lặp vô hạn
    }

    //  Tải âm thanh khi nhấn phím
    Mix_Chunk *gJump = graphics.loadSound("assets/jump.wav");
    if (!gJump) cout << "Failed to load jump sound! Error: " << Mix_GetError() << endl;

    //  Tạo background có hiệu ứng cuộn
    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    //  Tạo đối tượng Bird
    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture(BIRD_SPRITE_FILE);
    bird.init(birdTexture, BIRD_FRAMES, BIRD_CLIPS);

    int birdX = 100, birdY = 200;  // Vị trí ban đầu của chim
    int birdSpeed = 10;  // Tốc độ di chuyển

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        //  Điều khiển chim bằng W, A, S, D
        if (currentKeyStates[SDL_SCANCODE_W]) birdY -= birdSpeed;
        if (currentKeyStates[SDL_SCANCODE_S]) birdY += birdSpeed;
        if (currentKeyStates[SDL_SCANCODE_A]) birdX -= birdSpeed;
        if (currentKeyStates[SDL_SCANCODE_D]) birdX += birdSpeed;

        //  Phát âm thanh khi nhấn phím UP
        if (currentKeyStates[SDL_SCANCODE_UP] && gJump) {
            Mix_PlayChannel(-1, gJump, 0);
        }

        //  Cuộn background
        background.scroll(3);
        bird.tick(); // Cập nhật animation của chim

        //  Render các đối tượng
        graphics.prepareScene();
        graphics.render(background);  // Vẽ background
        graphics.render(birdX, birdY, bird);  // Vẽ con chim
        graphics.presentScene();

        SDL_Delay(100);
    }

    //  Giải phóng bộ nhớ
    if (gMusic) Mix_FreeMusic(gMusic);
    if (gJump) Mix_FreeChunk(gJump);
    Mix_CloseAudio();

    SDL_DestroyTexture(birdTexture);
    graphics.quit();

    return 0;
}
