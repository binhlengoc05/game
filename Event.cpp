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

void Event::mousePress(Graphics &graphics,SDL_Texture* background)
{
    int x,y;
    SDL_Event event;
    while (true) {
        SDL_GetMouseState(&x, &y);
        cerr << x << ", " << y << endl;
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
                 graphics.prepareScene(background);
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
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP] ) cerr << " Up";
        if (currentKeyStates[SDL_SCANCODE_DOWN] ) cerr << " Down";
        if (currentKeyStates[SDL_SCANCODE_LEFT] ) cerr << " Left";
        if (currentKeyStates[SDL_SCANCODE_RIGHT] ) cerr << " Right";
        if (currentKeyStates[SDL_SCANCODE_ESCAPE] ) exit(0);
        cerr << ".\n";

        SDL_Delay(100);
    }
}
    //trong hàm main
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
