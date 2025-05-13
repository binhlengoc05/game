#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"


void waitUntilKeyPressed();

struct Graphics{
    SDL_Renderer *renderer;
    SDL_Window *window;

    void logErrorAndExit(const char* msg, const char* error);

    void initSDL();//hàm khởi tạo cửa sổ

    void createRenderer();//hàm khởi tạo bút ve

    void quitSDL();//hàm giải phóng bộ nhớ

    void prepareScene(SDL_Texture * background);//hàm làm mới và bắt đầu đặt nền

    void presentScene();//hàm hiển thị toàn bộ nội dung đã vẽ lên màn hình

    void renderTexture(SDL_Texture *texture, int x, int y,int width=0,int height=0);// vẽ 1 texture lên màn hình tại vị trí (x,y) với kích thước width và height

    SDL_Texture *loadTexture(const char *filename);// tải 1 texture lên từ file hình ảnh

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);//sao chép (blit) một phần của texture vào một vị trí cụ thể trên màn hình với kích thước gốc

    //music
    Mix_Music* loadMusic(const char* path);

    void play(Mix_Music *gMusic);

    Mix_Chunk* loadSound(const char* path);

    void play(Mix_Chunk* gChunk);
};
#endif
