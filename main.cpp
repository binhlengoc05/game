#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "Event.h"
#include "Map.h"
#include "player.h"
#include "texture.h"
using namespace std;

void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    //cout << "Hello world!" << endl;
    Graphics graphics;
    graphics.initSDL();
    graphics.createRenderer();
/*---------chạy nhạc--------------------*/
    Mix_Music *gMusic = graphics.loadMusic("music/awesomeness.wav");
     graphics.play(gMusic);
    Mix_Chunk *gJump = graphics.loadSound("music/jump.mp3");

/*---------đọc map từ file------------*/
    Block** blocks=new Block* [MAP_HEIGHT];
    for(int i=0;i<MAP_HEIGHT;i++) blocks[i]=new Block [MAP_WIDTH];
    if (!loadMap("map.txt", blocks)) {
        cout << "Failed to load map!" << endl;
        for (int i = 0; i < MAP_HEIGHT; i++) {
            delete[] blocks[i];
        }
        delete[] blocks;
        graphics.quitSDL();
        return 1;
    }
/*----- khởi tạo phần background --------*/
    Start start;
    Tutorial tutorial;
    Endgame endgame;

    start.init(graphics);
    tutorial.init(graphics);
    endgame.init(graphics);

//  current screen: 0 = Start, 1 = Tutorial, 2 = Endgame
    int currentScreen = 0;
    SDL_Event event_mouse;
    StartBackground(graphics, currentScreen, event_mouse, start, tutorial);

/*---------khởi tạo nhân vật------------------*/

        Player player;
        player.baby(graphics);

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
                handleInput(event, player, blocks, gJump, graphics);
            }

            Uint32 currentTick = SDL_GetTicks();
            float deltaTime = (currentTick - lastTick) / 1000.0f;
            lastTick = currentTick;

            // Cập nhật camera
            cameraOffsetY -= scrollSpeed * deltaTime;
            if (cameraOffsetY < 0) cameraOffsetY = 0;

            // Cập nhật nhân vật
            updatePlayer(player, blocks, deltaTime, cameraOffsetY, scrollSpeed, graphics);

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
//    SDL_DestroyTexture( player1 );
//    player1 = NULL;

    for (int i = 0; i < MAP_HEIGHT; i++) {
        delete[] blocks[i];
    }
    delete[] blocks;

    graphics.quitSDL();
    return 0;
}




