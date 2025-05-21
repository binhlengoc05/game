#ifndef TEXTURE__H_
#define TEXTURE__H_

#include "graphics.h"
struct Start{
    SDL_Texture* background;
    SDL_Texture* kstart;
    SDL_Texture* ktutorial;
    SDL_Texture* kexit;

    SDL_Rect kstart_rect;
    SDL_Rect ktutorial_rect;
    SDL_Rect kexit_rect;

    SDL_Rect kstart_src;
    SDL_Rect ktutorial_src;
    SDL_Rect kexit_src;

    Start(){
        background = nullptr;
        kstart = nullptr;
        ktutorial = nullptr;
        kexit = nullptr;
    }

    void init(Graphics& graphics){
        background = graphics.loadTexture("background.jpg");
        kstart = graphics.loadTexture("key/start.png");
        ktutorial = graphics.loadTexture("key/tutorial.png");
        kexit = graphics.loadTexture("key/exit.png");

        kstart_rect = {TILE_SIZE * 12, TILE_SIZE * 4, TILE_SIZE * 4, TILE_SIZE * 5/4};
        ktutorial_rect = {TILE_SIZE * 12, TILE_SIZE * 6, TILE_SIZE * 4, TILE_SIZE * 5/4};
        kexit_rect = {TILE_SIZE * 12, TILE_SIZE * 8, TILE_SIZE * 4, TILE_SIZE * 5/4};

        int w, h;
        SDL_QueryTexture(kstart, nullptr, nullptr, &w, &h);
        kstart_src = {0, 0, w / 2, h};
        SDL_QueryTexture(ktutorial, nullptr, nullptr, &w, &h);
        ktutorial_src = {0, 0, w / 2, h};
        SDL_QueryTexture(kexit, nullptr, nullptr, &w, &h);
        kexit_src = {0, 0, w / 2, h};
    }

    void render(Graphics& graphics){
        graphics.prepareScene(background);
        //graphics.renderTexture(background,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        graphics.renderTexture(kstart,kstart_rect,kstart_src);
        graphics.renderTexture(ktutorial,ktutorial_rect,ktutorial_src);
        graphics.renderTexture(kexit,kexit_rect,kexit_src);
        graphics.presentScene();
    }

};

struct Tutorial{
    SDL_Texture* background;
    SDL_Texture* kback;

    SDL_Rect kback_rect;
    SDL_Rect kback_src;
    Tutorial(){
        background = nullptr;
        kback = nullptr;
    }

    void init(Graphics& graphics){
        background = graphics.loadTexture("tutorial.png");
        kback = graphics.loadTexture("key/back1.png");
        kback_rect = {TILE_SIZE *16, TILE_SIZE *9, TILE_SIZE *2, TILE_SIZE *1};

        int w, h;
        SDL_QueryTexture(kback, nullptr, nullptr, &w, &h);
        kback_src = {0, 0, w / 2, h};
    }

    void render(Graphics& graphics){
        graphics.prepareScene(background);
        //graphics.renderTexture(background,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        graphics.renderTexture(kback,kback_rect,kback_src);
        graphics.presentScene();
    }
};

struct Endgame{
    SDL_Texture* background;
    SDL_Texture* kexit;
    SDL_Texture* kback;

    SDL_Rect kexit_rect;
    SDL_Rect kexit_src;
    SDL_Rect kback_rect;
    SDL_Rect kback_src;
    Endgame(){
        background = nullptr;
        kexit = nullptr;
        kback = nullptr;
    }

    void init(Graphics& graphics){
        background = graphics.loadTexture("endgame.png");
        kexit = graphics.loadTexture("key/exit.png");
        kback = graphics.loadTexture("key/again.png");
        kexit_rect = {TILE_SIZE *14, TILE_SIZE *7, TILE_SIZE*4, TILE_SIZE *2};
        kback_rect = {TILE_SIZE *14, TILE_SIZE *4, TILE_SIZE*4, TILE_SIZE *2};

        int w, h;
        SDL_QueryTexture(kexit, nullptr, nullptr, &w, &h);
        kexit_src = {0, 0, w / 2, h};
        SDL_QueryTexture(kback, nullptr, nullptr, &w, &h);
        kback_src = {0, 0, w / 2, h};
    }

    void render(Graphics& graphics){
        graphics.prepareScene(background);
        //graphics.renderTexture(background,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        graphics.renderTexture(kexit,kexit_rect,kexit_src);
        graphics.renderTexture(kback,kback_rect,kback_src);
        graphics.presentScene();
    }
};



#endif
