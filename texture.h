#ifndef
#define

struct Start{
    SDL_Texture* background;
    SDL_Texture* kstart;
    SDL_Texture* ktutorial;
    SDL_Texture* kexit;

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
        bool exit = true;
        while(!exit){

        }
    }

};

struct Tutorial{
    SDL_Texture* background;
    SDL_Texture* kback;

    Tutorial(){
        background = nullptr;
        kback = nullptr;
    }

    void init(Graphics& graphics){
        background = graphics.loadTexture("tutorial.png");
        kback = graphics.loadTexture("key\back.png");
    }

    void render(Graphics& graphics){
        graphics.prepareScene();
        graphics.renderTexture(background,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

        SDL_Rect rect={17*TILE_SIZE , 11*TILE_SIZE , TILE_SIZE/4*3 , TILE_SIZE/2 };//x,y,w,h;
        SDL_Rect Src;
        SDL_QueryTexture(kback, NULL, NULL, &Src.w, &Src.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
        Src={0 , 0 , Src.w /2 , Src.h};
        SDL_RenderCopy(graphics.renderer,kback,&Src,&rect);

        graphics.presentScene();
    }
};

struct Texture{

    SDL_Texture* tutorial;
    SDL_Texture* kback;


};

#endif
