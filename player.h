#ifndef PLAYER__H_
#define PLAYER__H_

#include "Map.h"

struct Player {
    float x, y;        // Tọa độ trong không gian game
    float vx, vy;      // Vận tốc
    float Fmove;
    float Fjump;
    bool is_jumping;   // Trạng thái nhảy

    bool isBoy;
    bool isMan;
    bool isOld;

    SDL_Texture* texture; //lưu ảnh
    SDL_Rect rect;     // lưu vị trí renderer, kích thước của ảnh
    SDL_Rect playerSrc;// tại vị trí của anh,lấy 1 khung ảnh có chiều rộng và cao

    Player();

    void man(Graphics &graphics);
    void baby(Graphics &graphics);
    void boy(Graphics &graphics);
    void old(Graphics &graphics);
};

bool isGameOver(Player& player, float cameraOffsetY);

void handleInput(SDL_Event& event, Player& player,Block** blocks, Mix_Chunk *gJump, Graphics& graphics);

void updatePlayer(Player& player, Block** blocks, float deltaTime, float cameraOffsetY, float scrollSpeed, Graphics &graphics, bool& quit);

void drawPlayer(Player player,Graphics &graphics,float cameraOffsetY);

#endif // PLAYER__H_
