#include "Event.h"
#include <SDL.h>
#include <iostream>

using namespace std;

bool isMouseInsideRect(int mouseX, int mouseY, SDL_Rect rect) {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
            mouseY >= rect.y && mouseY <= rect.y + rect.h);
}

void StartBackground(Graphics& graphics, int currentScreen, SDL_Event event_mouse, Start start, Tutorial tutorial){
    bool running = true;

    while (running) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Update source rects based on mouse position (hover effect)
        int w, h;
        SDL_QueryTexture(start.kstart, nullptr, nullptr, &w, &h);
        start.kstart_src.x = isMouseInsideRect(mouseX, mouseY, start.kstart_rect) ? w / 2 : 0;
        SDL_QueryTexture(start.ktutorial, nullptr, nullptr, &w, &h);
        start.ktutorial_src.x = isMouseInsideRect(mouseX, mouseY, start.ktutorial_rect) ? w / 2 : 0;
        SDL_QueryTexture(start.kexit, nullptr, nullptr, &w, &h);
        start.kexit_src.x = isMouseInsideRect(mouseX, mouseY, start.kexit_rect) ? w / 2 : 0;

        SDL_QueryTexture(tutorial.kback, nullptr, nullptr, &w, &h);
        tutorial.kback_src.x = isMouseInsideRect(mouseX, mouseY, tutorial.kback_rect) ? w / 2 : 0;

        // Handle events
        while (SDL_PollEvent(&event_mouse)) {
            switch (event_mouse.type) {
                case SDL_QUIT:
                    cerr << "Quit game!" << endl;
                    exit(0);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event_mouse.button.button == SDL_BUTTON_LEFT) {
                        if (currentScreen == 0) { // Start screen
                            if (isMouseInsideRect(mouseX, mouseY, start.kstart_rect)) {
                                cerr << "Start button clicked!" << endl;
                                running = false;
                            } else if (isMouseInsideRect(mouseX, mouseY, start.ktutorial_rect)) {
                                cerr << "Tutorial button clicked!" << endl;
                                currentScreen = 1; // Transition to Tutorial
                            } else if (isMouseInsideRect(mouseX, mouseY, start.kexit_rect)) {
                                cerr << "Exit button clicked!" << endl;
                                running = false;
                                cerr << "Quit game!" << endl;
                                exit(0);
                                break;
                            }
                        } else if (currentScreen == 1) { // Tutorial screen
                            if (isMouseInsideRect(mouseX, mouseY, tutorial.kback_rect)) {
                                cerr << "Back button clicked!" << endl;
                                currentScreen = 0; // Back to Start
                            }
                        }
                    }
                }
        }

        // Render current screen
        if (currentScreen == 0) {
            start.render(graphics);
        }
        else if (currentScreen == 1) {
            tutorial.render(graphics);
        }
        SDL_Delay(10);
    }
}
void EndBackground(Graphics& graphics, SDL_Event event_mouse, Endgame endgame){
    bool running = true;

    while (running) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Update source rects based on mouse position (hover effect)
        int w, h;
        SDL_QueryTexture(endgame.kexit, nullptr, nullptr, &w, &h);
        endgame.kexit_src.x = isMouseInsideRect(mouseX, mouseY, endgame.kexit_rect) ? w / 2 : 0;
        SDL_QueryTexture(endgame.kexit, nullptr, nullptr, &w, &h);
        endgame.kback_src.x = isMouseInsideRect(mouseX, mouseY, endgame.kback_rect) ? w / 2 : 0;
        // Handle events
        while (SDL_PollEvent(&event_mouse)) {
            switch (event_mouse.type) {
                case SDL_QUIT:
                    cerr << "Quit game!" << endl;
                    exit(0);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event_mouse.button.button == SDL_BUTTON_LEFT) {
                       if (isMouseInsideRect(mouseX, mouseY, endgame.kexit_rect)) {
                                cerr << "Exit button clicked!" << endl;
                                running = false;
                                cerr << "Quit game!" << endl;
                                exit(0);
                                break;
                            }
                        }
                        else if (isMouseInsideRect(mouseX, mouseY, endgame.kback_rect)) {
                                cerr << "Back button clicked!" << endl;
                                running = false;
                                break;
                        }
            }
        }
        endgame.render(graphics);
        SDL_Delay(10);
    }
}
//void Event::mouse()
//{
//    SDL_Event event;
//    int x,y;
//    while (true) {
//        SDL_PollEvent(&event);
//        SDL_GetMouseState(&x, &y);
//        cerr << x << ", " << y << endl;
//        switch (event.type) {
//            case SDL_QUIT:
//                 exit(0);
//                 break;
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.sym){
//                        case SDLK_ESCAPE:
//                            cerr << "Nhan ESC (thoat)" << endl;
//                            exit(0);
//                            break;
//                        default:
//                            cerr << "Phim khac: " << SDL_GetKeyName(event.key.keysym.sym) << endl;
//                            break;
//                    }
//                break;
//        }
//        SDL_Delay(100);
//    }
//}
//
//void Event::mousePress(Graphics &graphics,SDL_Texture* background)
//{
//    int x,y;
//    SDL_Event event;
//    while (true) {
//        SDL_GetMouseState(&x, &y);
//        cerr << x << ", " << y << endl;
//        SDL_PollEvent(&event);
//        switch (event.type) {
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.sym){
//                    case SDLK_ESCAPE:
//                        cerr << "Nhan ESC (thoat)" << endl;
//                        exit(0);
//                        break;
//                    }
//                break;
//            case SDL_QUIT:// ấn chuột vào x cửa sổ
//                 exit(0);
//                 break;
//            case SDL_MOUSEBUTTONDOWN:
//                 cerr << "Down at (" << x << ", " << y << ")\n";
//                 break;
//            case SDL_MOUSEBUTTONUP:
//                 cerr << "Up at (" << x << ", " << y << ")\n";
//                 break;
//        }
//        SDL_Delay(100);
//    }
//
//}
//
//void Event::keyp()
//{
//    bool quit = false;
//    SDL_Event event;
//    while (!quit) {
//        //Handle events on queue
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) quit = true;
//        }
//
//        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
//
//        if (currentKeyStates[SDL_SCANCODE_UP] ) cerr << " Up";
//        if (currentKeyStates[SDL_SCANCODE_DOWN] ) cerr << " Down";
//        if (currentKeyStates[SDL_SCANCODE_LEFT] ) cerr << " Left";
//        if (currentKeyStates[SDL_SCANCODE_RIGHT] ) cerr << " Right";
//        if (currentKeyStates[SDL_SCANCODE_ESCAPE] ) exit(0);
//        cerr << ".\n";
//
//        SDL_Delay(100);
//    }
//}

