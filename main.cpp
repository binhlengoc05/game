#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

//void logErrorAndExit(const char* msg, const char* error);
//SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
//SDL_Renderer* createRenderer(SDL_Window* window);
//void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
//void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer);
//SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);

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

    SDL_Rect playerSrc;
    playerSrc.x=playerRect.w/4.0*3.0;// cột - lấy ảnh thứ tư của hình man run2 với kích thước rộng playerSrc.w
    playerSrc.y=0;//hàng
    playerSrc.w=playerRect.w/4.0;
    playerSrc.h=playerRect.h;

    playerRect.x=0;
    playerRect.y=0;
    playerRect.w=SCREEN_WIDTH/19.0; // giảm độ rộng thực tế đi 11 lần, nếu ko có hàm này kích thước bằng ảnh gốc
    playerRect.h=SCREEN_HEIGHT/11.0;

    //SDL_RenderCopy(renderer,player,NULL,&playerRect);// trường hợp lấy toàn bộ ảnh player
    SDL_RenderCopy(graphics.renderer,player,&playerSrc,&playerRect);

    graphics.presentScene();

    waitUntilKeyPressed();

    SDL_DestroyTexture( background );
    background = NULL;
    SDL_DestroyTexture( player );
    player = NULL;

    graphics.quitSDL();

    return 0;
}







//
//
//
///* game loop với logic tối thiểu chỉ đủ chạy được chương trình */
////hàm báo lỗi
//void logErrorAndExit(const char* msg, const char* error)
//{
//    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
//    SDL_Quit();
//}
//
////hàm khởi tạo
//SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
//{
//    //hàm nếu không khởi tạo thành công thì trả vê báo lỗi
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)//=0 báo lỗi
//        logErrorAndExit("SDL_Init", SDL_GetError());
////
//    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);//SDL_WINDOWPOS_CENTERED : trung tâm theo chiều dọc và ngang
//    //full screen
//    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
//    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
//
//    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
//        logErrorAndExit( "SDL_image error:", IMG_GetError());
//
//    return window;
//}
//
//SDL_Renderer* createRenderer(SDL_Window* window)
//{
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
//                                              SDL_RENDERER_PRESENTVSYNC);
//    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
//    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
//
//    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());
//
//    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
//    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//    return renderer;
//}
//
//void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
//{
//    IMG_Quit();
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//}
//
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
//
//void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer)
//{
//	SDL_Rect dest;
//
//	dest.x = x;
//	dest.y = y;
//	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
//
//	SDL_RenderCopy(renderer, texture, NULL, &dest);
//}
//
//SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
//{
//	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
//
//	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
//	if (texture == NULL)
//        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
//
//	return texture;
//}
