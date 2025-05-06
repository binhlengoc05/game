#include "Event.h"
#include <SDL.h>
#include <iostream>
#include "graphics.h"
using namespace std;

void Event::mouse()
{
    SDL_Event event;
    int x,y;
    while (true) {
        SDL_PollEvent(&event);
        SDL_GetMouseState(&x, &y);
        cerr << x << ", " << y << endl;
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            cerr << "Nhan ESC (thoat)" << endl;
                            exit(0);
                            break;
                        default:
                            cerr << "Phim khac: " << SDL_GetKeyName(event.key.keysym.sym) << endl;
                            break;
                    }
                break;
        }
        SDL_Delay(100);
    }
}

void Event::mousePress(Graphics &graphics)
{
    SDL_Texture* player=nullptr;
    SDL_Rect playerRect;
    SDL_Rect playerSrc;
    player=graphics.loadTexture("man run1.png");
    SDL_QueryTexture(player, NULL, NULL, &playerRect.w, &playerRect.h);
    playerSrc={0 , 0 , playerRect.w/4 , playerRect.h};
    playerRect={0 , 0 , SCREEN_WIDTH/19 , SCREEN_HEIGHT/11 };

    int x,y;
    SDL_Event event;
    while (true) {
        SDL_GetMouseState(&x, &y);

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        cerr << "Nhan ESC (thoat)" << endl;
                        exit(0);
                        break;
                    }
                break;
            case SDL_QUIT:// ấn chuột vào x cửa sổ
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 cerr << "Down at (" << x << ", " << y << ")\n";
                 playerRect={x , y , SCREEN_WIDTH/19 , SCREEN_HEIGHT/11 };
                 SDL_RenderCopy(graphics.renderer,player,&playerSrc,&playerRect);
                 graphics.presentScene();
                 break;
            case SDL_MOUSEBUTTONUP:
                 cerr << "Up at (" << x << ", " << y << ")\n";
                 break;
        }
        SDL_Delay(100);
    }

}

void Event::keyp()
{

}

