#ifndef PLAYER__H_
#define PLAYER__H_

#include "Map.h"

struct Player {
    float x, y;        // Tọa độ trong không gian game
    float vx, vy;      // Vận tốc
    float Fmove;
    float Fjump;
    bool is_jumping;   // Trạng thái nhảy

    SDL_Texture* texture; //lưu ảnh
    SDL_Rect rect;     // lưu vị trí renderer, kích thước của ảnh
    SDL_Rect playerSrc;// tại vị trí của anh,lấy 1 khung ảnh có chiều rộng và cao

    Player(){
        x = SCREEN_WIDTH / 2;
        y = (MAP_HEIGHT * TILE_SIZE - SCREEN_HEIGHT) - 100;
        vx = 0;
        vy = 0;
        Fmove = 0;
        Fjump = 0;
        is_jumping = false;
    }
    void man(Graphics &graphics){
        texture=graphics.loadTexture("man.png");
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
        playerSrc={rect.w/4*0 , 0 , rect.w/4 , rect.h};//x,y,w,h
        rect={0 , 0 , SCREEN_WIDTH/19 , SCREEN_HEIGHT/11 };//x,y,w,h
        Fmove = 220.0f;
        Fjump = 540.0f;
    }
    void baby(Graphics &graphics){
        texture=graphics.loadTexture("baby.png");
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
        playerSrc={rect.w/4*0 , 0 , rect.w/4 , rect.h};//x,y,w,h
        rect={0 , 0 , SCREEN_WIDTH/19 , SCREEN_HEIGHT/11 };//x,y,w,h
        Fmove = 100.0f;
        Fjump = 0;
    }
    void boy(Graphics &graphics){
        texture=graphics.loadTexture("boy.png");
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
        playerSrc={rect.w/4*0 , 0 , rect.w/4 , rect.h};//x,y,w,h
        rect={0 , 0 , SCREEN_WIDTH/19-20 , SCREEN_HEIGHT/11 };//x,y,w,h
        Fmove = 200.0f;
        Fjump = 450.0f;
    }
    void old(Graphics &graphics){
        texture=graphics.loadTexture("old.png");
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
        playerSrc={rect.w/4*0 , 0 , rect.w/4 , rect.h};//x,y,w,h
        rect={0 , 0 , SCREEN_WIDTH/19-20 , SCREEN_HEIGHT/11 };//x,y,w,h
        Fmove = 100.0f;
        Fjump = 0;
    }
};

bool isGameOver(Player& player, float cameraOffsetY);

void handleInput(SDL_Event& event, Player& player,Block** blocks);

void updatePlayer(Player& player, Block** blocks, float deltaTime, float cameraOffsetY, float scrollSpeed);

void drawPlayer(Player player,Graphics &graphics,float cameraOffsetY);

#endif // PLAYER__H_
