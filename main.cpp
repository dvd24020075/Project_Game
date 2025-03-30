#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "def.h"
#include "graphics.h"
#include "game.h"
#include "bomb.h"
#include "coin.h"
#include "explosion.h"
#include "score_effect.h"

using namespace std;

int score = 0;
SDL_Texture* coinTexture;
TTF_Font* font;

enum GameState {
    STATE_START,
    STATE_PLAYING
};

GameState gameState = STATE_START;
SDL_Texture* startTextTexture = nullptr;
SDL_Texture* startScreenTexture = nullptr;

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0)));

    Graphics graphics;
    graphics.init();

    // Initialize SDL_mixer and SDL_ttf
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << endl;
        return -1;
    }
    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! Error: " << TTF_GetError() << endl;
        return -1;
    }

    // Load sounds and music
    Mix_Music* gMusic = graphics.loadMusic("music/music_00.mp3");
    if (gMusic) Mix_PlayMusic(gMusic, -1);
    Mix_Chunk* gJump = graphics.loadSound("music/jump.wav");
    Mix_Chunk* gExplosionSound = graphics.loadSound("music/explosion.wav");
    Mix_Chunk* gCoinSound = graphics.loadSound("music/coin.wav");
    Mix_Music* gGameOverMusic = graphics.loadMusic("music/gameover.mp3");

    // Load start screen and create START text
    startScreenTexture = graphics.loadTexture("img/start_screen.png");
    if (!startScreenTexture) {
        cout << "Failed to load start screen texture! Error: " << SDL_GetError() << endl;
        return -1;
    }
    // Load font and create START text texture
    font = TTF_OpenFont("font/font.ttf", 48);
    if (!font) {
        cout << "Failed to load font! Error: " << TTF_GetError() << endl;
        return -1;
    }
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* startTextSurface = TTF_RenderText_Solid(font, "START", white);
    if (startTextSurface) {
        startTextTexture = SDL_CreateTextureFromSurface(graphics.renderer, startTextSurface);
        SDL_FreeSurface(startTextSurface);
    } else {
        cout << "Failed to create START text! Error: " << TTF_GetError() << endl;
    }

    // Load common resources
    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture(BIRD_SPRITE_FILE);
    bird.init(birdTexture, BIRD_FRAMES, BIRD_CLIPS);

    SDL_Texture* bombTexture = graphics.loadTexture("img/bomb.png");
    SDL_Texture* explosionTexture = graphics.loadTexture("img/explosion.png");
    SDL_Texture* gameOverTexture = graphics.loadTexture("img/gameover.png");
    coinTexture = graphics.loadTexture("img/coin.png");

    // Game variables
    int birdX = 100, birdY = 200;
    int birdSpeed = 10;
    vector<Bomb> bombs;
    vector<Explosion> explosions;
    vector<Coin> coins;
    vector<ScoreEffect> scoreEffects;
    Uint32 lastBombSpawnTime = SDL_GetTicks();
    const int bombSpawnInterval = 2000;
    Uint32 lastCoinSpawnTime = SDL_GetTicks();
    const int coinSpawnInterval = 4000;
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = true;

            // Nếu ở màn hình START, kiểm tra nhấn chuột hoặc phím
            if (gameState == STATE_START) {
                if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX = e.button.x;
                        int mouseY = e.button.y;
                        SDL_Rect startTextRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 20, 100, 40 };
                        if (mouseX >= startTextRect.x && mouseX <= startTextRect.x + startTextRect.w &&
                            mouseY >= startTextRect.y && mouseY <= startTextRect.y + startTextRect.h) {
                            gameState = STATE_PLAYING;
                        }
                    }
                }
            }
        }

         // Nếu game vẫn ở màn hình Start, hiển thị màn hình Start
    if (gameState == STATE_START) {
        graphics.prepareScene();
        SDL_RenderCopy(graphics.renderer, startScreenTexture, nullptr, nullptr);

        // Chèn đoạn mã tạo và render chữ "START" vào đây:
        SDL_Color textColor = {255, 255, 255, 255};  // Màu trắng
        SDL_Surface* startTextSurface = TTF_RenderText_Solid(font, "START", textColor);
        if (startTextSurface) {
            startTextTexture = SDL_CreateTextureFromSurface(graphics.renderer, startTextSurface);
            SDL_Rect startTextRect = {
                SCREEN_WIDTH / 2 - startTextSurface->w / 2,
                SCREEN_HEIGHT / 2 - startTextSurface->h / 2,
                startTextSurface->w,
                startTextSurface->h
            };
            SDL_FreeSurface(startTextSurface);
            SDL_RenderCopy(graphics.renderer, startTextTexture, nullptr, &startTextRect);
        }

        graphics.presentScene();
        SDL_Delay(100);
        continue; // Không chạy phần game update nếu chưa chuyển sang STATE_PLAYING
    }

        // Update game logic...
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W]) birdY -= birdSpeed;
        if (keys[SDL_SCANCODE_S]) birdY += birdSpeed;
        if (keys[SDL_SCANCODE_A]) birdX -= birdSpeed;
        if (keys[SDL_SCANCODE_D]) birdX += birdSpeed;
        if (keys[SDL_SCANCODE_UP] && gJump) Mix_PlayChannel(-1, gJump, 0);

        // Lấy kích thước của chim
        const SDL_Rect* birdClip = bird.getCurrentClip();
        int birdWidth = birdClip->w;
        int birdHeight = birdClip->h;

                // Cho phép chim đi ra ngoài 10 pixel (sát cửa sổ hơn)
        if (birdX < -10)
            birdX = -10;
        else if (birdX > SCREEN_WIDTH - birdWidth + 10)
            birdX = SCREEN_WIDTH - birdWidth + 10;

        if (birdY < -10)
            birdY = -10;
        else if (birdY > SCREEN_HEIGHT - birdHeight + 10)
            birdY = SCREEN_HEIGHT - birdHeight + 10;
        background.scroll(3);
        bird.tick();

//         const SDL_Rect* birdClip = bird.getCurrentClip();
        int birdCenterX = birdX + birdClip->w / 2;
        int birdCenterY = birdY + birdClip->h / 2;

         Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastBombSpawnTime >= bombSpawnInterval) {
            int bombXPos = rand() % (SCREEN_WIDTH - 32);
            bombs.push_back(Bomb(bombXPos, 0, bombTexture));
            lastBombSpawnTime = currentTime;
        }
        if (currentTime - lastCoinSpawnTime >= coinSpawnInterval) {
            int coinX = rand() % (SCREEN_WIDTH - 32);
            int coinY = rand() % (SCREEN_HEIGHT - 32);
            coins.push_back(Coin(coinX, coinY, coinTexture));
            lastCoinSpawnTime = currentTime;
        }

        // Kiểm tra va chạm giữa chim và bom
        for (auto it = bombs.begin(); it != bombs.end(); ) {
            it->update();
            if (it->y > SCREEN_HEIGHT) {
                it = bombs.erase(it);
            } else {
                int bombCenterX = static_cast<int>(it->x) + 35;
                int bombCenterY = static_cast<int>(it->y) + 35;
                float dx = birdCenterX - bombCenterX;
                float dy = birdCenterY - bombCenterY;
                float distance = sqrt(dx * dx + dy * dy);
                if (distance < COLLISION_THRESHOLD) {
                    if (gMusic) Mix_HaltMusic();
                    if (gExplosionSound) Mix_PlayChannel(-1, gExplosionSound, 0);
                    explosions.push_back(Explosion(it->x, it->y, explosionTexture));
                    it = bombs.erase(it);
                    Uint32 explosionStartTime = SDL_GetTicks();
                    while (SDL_GetTicks() - explosionStartTime < 1000) {
                        for (auto& exp : explosions) exp.update();
                        graphics.prepareScene();
                        graphics.render(background);
                        graphics.render(birdX, birdY, bird);
                        for (const Bomb& bomb : bombs) bomb.render(graphics.renderer);
                        for (const Explosion& exp : explosions) exp.render(graphics.renderer);
                        graphics.presentScene();
                        SDL_Delay(100);
                    }
                    if (gMusic) Mix_HaltMusic();
                    if (gGameOverMusic) Mix_PlayMusic(gGameOverMusic, 0);
                    quit = true;
                    break;
                }
                ++it;
            }
        }

        // Kiểm tra và xử lý coin
        for (auto it = coins.begin(); it != coins.end(); ) {
            int coinCenterX = static_cast<int>(it->x) + 16;
            int coinCenterY = static_cast<int>(it->y) + 16;
            float dx = birdCenterX - coinCenterX;
            float dy = birdCenterY - coinCenterY;
            float distance = sqrt(dx * dx + dy * dy);
            // Nếu coin đã tồn tại quá 5 giây, xóa coin
            if (SDL_GetTicks() - it->spawnTime >= 7000) {
                it = coins.erase(it);
            }
            else if (distance < 50.0f) {
                score += 10;
                if (gCoinSound) Mix_PlayChannel(-1, gCoinSound, 0);
                scoreEffects.push_back(ScoreEffect(it->x, it->y));
                it = coins.erase(it);
            } else {
                ++it;
            }
        }

        // Cập nhật hiệu ứng "+10"
        for (auto it = scoreEffects.begin(); it != scoreEffects.end();) {
            if (SDL_GetTicks() - it->startTime > 3000)
                it = scoreEffects.erase(it);
            else {
                it->update();
                ++it;
            }
        }

        // Cập nhật hiệu ứng vụ nổ
        for (auto it = explosions.begin(); it != explosions.end();) {
            if (it->update())
                it = explosions.erase(it);
            else
                ++it;
        }

        // Render scene
        graphics.prepareScene();
        graphics.render(background);
        graphics.render(birdX, birdY, bird);
        for (const Bomb& bomb : bombs) bomb.render(graphics.renderer);
        for (const Coin& coin : coins) coin.render(graphics.renderer);
        for (const Explosion& exp : explosions) exp.render(graphics.renderer);

         // Render score
        SDL_Color scoreColor = {255, 255, 255, 255};
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, ("Score: " + to_string(score)).c_str(), scoreColor);
        if (scoreSurface) {
            SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(graphics.renderer, scoreSurface);
            SDL_Rect scoreRect = {10, 10, scoreSurface->w, scoreSurface->h};
            SDL_RenderCopy(graphics.renderer, scoreTexture, nullptr, &scoreRect);
            SDL_DestroyTexture(scoreTexture);
            SDL_FreeSurface(scoreSurface);
        }
        // Render score effects
        for (const ScoreEffect& effect : scoreEffects) {
            SDL_Surface* effectSurface = TTF_RenderText_Blended(font, "+10", effect.color);
            if (effectSurface) {
                SDL_Texture* effectTexture = SDL_CreateTextureFromSurface(graphics.renderer, effectSurface);
                SDL_Rect effectRect = { static_cast<int>(effect.x), static_cast<int>(effect.y), effectSurface->w, effectSurface->h };
                SDL_RenderCopy(graphics.renderer, effectTexture, nullptr, &effectRect);
                SDL_DestroyTexture(effectTexture);
                SDL_FreeSurface(effectSurface);
            }
        }

        graphics.presentScene();
        SDL_Delay(100);
    }

    // Hiển thị màn hình Game Over
    graphics.prepareScene();
    SDL_Rect gameOverRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(graphics.renderer, gameOverTexture, nullptr, &gameOverRect);
    SDL_Surface* finalScoreSurface = TTF_RenderText_Solid(font, (" Your Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
        if (finalScoreSurface) {
            SDL_Texture* finalScoreTexture = SDL_CreateTextureFromSurface(graphics.renderer, finalScoreSurface);
            if (finalScoreTexture) {
                // Tính toán vị trí để in điểm nằm giữa màn hình Game Over
                SDL_Rect finalScoreRect = {
                    SCREEN_WIDTH / 2 - finalScoreSurface->w / 2,
                    SCREEN_HEIGHT / 2 - finalScoreSurface->h / 2 -210,
                    finalScoreSurface->w,
                    finalScoreSurface->h
                };
                SDL_RenderCopy(graphics.renderer, finalScoreTexture, nullptr, &finalScoreRect);
                SDL_DestroyTexture(finalScoreTexture);
            } else {
                std::cout << "Failed to create final score texture! Error: " << SDL_GetError() << std::endl;
            }
            SDL_FreeSurface(finalScoreSurface);
        }
    graphics.presentScene();
    SDL_Delay(7000);


    // Giải phóng tài nguyên
    if (gJump) Mix_FreeChunk(gJump);
    if (gCoinSound) Mix_FreeChunk(gCoinSound);
    Mix_CloseAudio();
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture(bombTexture);
    SDL_DestroyTexture(explosionTexture);
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(startScreenTexture);
    if (gExplosionSound) Mix_FreeChunk(gExplosionSound);
    SDL_DestroyTexture(coinTexture);
    if (startTextTexture) SDL_DestroyTexture(startTextTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    graphics.quit();

    return 0;
}
