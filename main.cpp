#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    //cout << "Hello world!" << endl;
    Graphics graphics;
    graphics.initSDL();
    graphics.createRenderer();

    SDL_Texture* background = graphics.loadTexture("background 2.jpg");
    graphics.prepareScene(background);
    graphics.presentScene();

    waitUntilKeyPressed();

    SDL_Texture* player=graphics.loadTexture("man run2.png");
    // cần sửa tiếp

    SDL_Rect playerRect;//khung hình chữ nhật của player
    SDL_QueryTexture(player, NULL, NULL, &playerRect.w, &playerRect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h

/*---------khởi tạo nhân vật------------------*/
    SDL_Rect playerSrc={playerRect.w/4*3 , 0 , playerRect.w/4 , playerRect.h};
 /*hàm trên tương đương*/
//    playerSrc.x=playerRect.w/4.0*3.0;// cột - lấy ảnh thứ tư của hình man run2 với kích thước rộng playerSrc.w
//    playerSrc.y=0;//hàng
//    playerSrc.w=playerRect.w/4.0;
//    playerSrc.h=playerRect.h;

    playerRect={0 , 0 , SCREEN_WIDTH/19 , SCREEN_HEIGHT/11 };
//    playerRect.x=0;
//    playerRect.y=0;
//    playerRect.w=SCREEN_WIDTH/19.0; // giảm độ rộng thực tế đi 11 lần, nếu ko có hàm này kích thước bằng ảnh gốc
//    playerRect.h=SCREEN_HEIGHT/11.0;
//
//    SDL_RenderCopy(graphics.renderer,player,NULL,&playerRect);// trường hợp lấy toàn bộ ảnh player
    SDL_RenderCopy(graphics.renderer,player,&playerSrc,&playerRect);

    graphics.presentScene();

//    SDL_Texture* player=graphics.loadTexture("man run.png");
//    graphics.renderTexture(player,70,70);
//    graphics.presentScene();

    waitUntilKeyPressed();

    SDL_DestroyTexture( background );
    background = NULL;
    SDL_DestroyTexture( player );
    player = NULL;

    graphics.quitSDL();
    return 0;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
