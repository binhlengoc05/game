#ifndef
#define

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
        background = graphics.loadTexture("background 2.jpg");
        kstart = graphics.loadTexture("key\start.png");
        ktutorial = graphics.loadTexture("key\tutorial.png");
        kexit = graphics.loadTexture("key\exit.png");
    }

    void render(Graphics& graphics){
        graphics.prepareScene();
        graphics.renderTexture(background,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
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
        kback = graphics.loadTexture("key\back.png");
        kback_rect = {TILE_SIZE *16, TILE_SIZE *9, TILE_SIZE *1, TILE_SIZE *2};
    }

    void render(Graphics& graphics){
        graphics.prepareScene();
        graphics.renderTexture(background,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        graphics.renderTexture(kback,kback_rect,kback_src);
        graphics.presentScene();
    }
};

struct Endgame{
    SDL_Texture* background;
    SDL_Texture* kexit;

    SDL_Rect kexit_rect;
    SDL_Rect kexit_src;
    Tutorial(){
        background = nullptr;
        kback = nullptr;
    }

    void init(Graphics& graphics){
        background = graphics.loadTexture("endgame.png");
        kexit = graphics.loadTexture("key\back.png");
        kexit_rect = {TILE_SIZE *16, TILE_SIZE *9, TILE_SIZE *1, TILE_SIZE *2};
    }

    void render(Graphics& graphics){
        graphics.prepareScene();
        graphics.renderTexture(background,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        graphics.renderTexture(kexit,kexit_rect,kexit_src);
        graphics.presentScene();
    }
};

#endif
