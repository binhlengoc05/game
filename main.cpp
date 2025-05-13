#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "Event.h"
#include "Map.h"
#include "player.h"
using namespace std;

void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    //cout << "Hello world!" << endl;
    Graphics graphics;
    graphics.initSDL();
    graphics.createRenderer();

/*---------chạy nhạc--------------------*/
    Mix_Music *gMusic = graphics.loadMusic("song.mp3");
    graphics.play(gMusic);
/*---------đọc map từ file------------*/
    Block** blocks=new Block* [MAP_HEIGHT];
    for(int i=0;i<MAP_HEIGHT;i++) blocks[i]=new Block [MAP_WIDTH];
    if (!loadMap("map.txt", blocks)) {
        cout << "Failed to load map!" << endl;
        graphics.quitSDL();
        return 1;
    }
/*---------vẽ nền-----------------------*/
    SDL_Texture* background = graphics.loadTexture("background 1.jpg");
    graphics.prepareScene(background);
    graphics.presentScene();

    waitUntilKeyPressed();
/*---------khởi tạo nhân vật------------------*/
    // Khởi tạo nhân vật
    Player player;

    SDL_Texture* player1=graphics.loadTexture("man run1.png");

    SDL_Rect playerRect;//khung hình chữ nhật của player
    SDL_QueryTexture(player1, NULL, NULL, &playerRect.w, &playerRect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h

    SDL_Rect playerSrc={playerRect.w/4*0 , 0 , playerRect.w/4 , playerRect.h};//x,y,w,h
    playerRect={0 , 0 , SCREEN_WIDTH/19 , SCREEN_HEIGHT/11 };//x,y,w,h
    SDL_RenderCopy(graphics.renderer,player1,&playerSrc,&playerRect);

    graphics.presentScene();

//    SDL_Texture* player=graphics.loadTexture("man run.png");
//    graphics.renderTexture(player,70,70);
//    graphics.presentScene();
/*----------nghịch phím--------------------*/
    //Event event;
    //event.keyp();
/*----------nghịch mouse_pressed-----------*/

//    SDL_RenderClear(graphics.renderer);
//    cerr<<"event mouse, please press key:\n";
//    waitUntilKeyPressed();
//
//    Event event;
//    event.mousePress(graphics,background);
/*--------run game-----------------*/

    // Bắt đầu từ đáy bản đồ
    float cameraOffsetY = MAP_HEIGHT * TILE_SIZE - SCREEN_HEIGHT;
    float scrollSpeed = 50.0f;
    Uint32 lastTick = SDL_GetTicks();

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
            handleInput(event, player);
        }

        Uint32 currentTick = SDL_GetTicks();
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        // Cập nhật camera
        cameraOffsetY -= scrollSpeed * deltaTime;
        if (cameraOffsetY < 0) cameraOffsetY = 0;

        // Cập nhật nhân vật
        updatePlayer(player, blocks, deltaTime, cameraOffsetY, scrollSpeed);

        // Kiểm tra thua game
        if (isGameOver(player, cameraOffsetY)) {
            cout << "Game Over!" << endl;
            quit = true;
        }

        drawMap(graphics,blocks,cameraOffsetY);

        // Vẽ nhân vật
        drawPlayer(player,graphics,cameraOffsetY);

        graphics.presentScene();
        SDL_Delay(16); // ~60 FPS
    }

/*-----giải phóng window,rendered,....----------*/
    SDL_DestroyTexture( background );
    background = NULL;
    SDL_DestroyTexture( player1 );
    player1 = NULL;

    for (int i = 0; i < MAP_HEIGHT; i++) {
        delete[] blocks[MAP_WIDTH];
    }
    delete[] blocks;

    graphics.quitSDL();
    return 0;
}


