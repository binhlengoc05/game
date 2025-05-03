#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
//khởi tạo cửa sổ

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 900;
const char* WINDOW_TITLE = "Hello World!";

//hàm báo lỗi
void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

//hàm khởi tạo
SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    //hàm nếu không khởi tạo thành công thìtrả vê báo lỗi
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
    return window;
}

int main(int argc, char* argv[])
{
    //cout << "Hello world!" << endl;
    SDL_Window* window=initSDL(SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    SDL_Delay(2000);
    return 0;
}
/* game loop với logic tối thiểu chỉ đủ chạy được chương trình */
