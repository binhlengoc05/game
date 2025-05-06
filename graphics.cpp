    #include <iostream>
    #include <SDL.h>
    #include <SDL_image.h>
    #include "defs.h"
    #include "graphics.h"

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

   void Graphics::logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

    //hàm khởi tạo
    void Graphics::initSDL()
    {
        //hàm nếu không khởi tạo thành công thì trả vê báo lỗi
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)//=0 báo lỗi
            logErrorAndExit("SDL_Init", SDL_GetError());
    //
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);//SDL_WINDOWPOS_CENTERED : trung tâm theo chiều dọc và ngang
        //full screen
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

    }


    void Graphics::createRenderer()
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                                  SDL_RENDERER_PRESENTVSYNC);
        //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
        //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    }

    void Graphics::quitSDL()
    {
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Graphics::prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void Graphics::presentScene()
    {
        SDL_RenderPresent(renderer);
    }


    void Graphics::renderTexture(SDL_Texture *texture, int x, int y,int width,int height)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;

        // Nếu width và height không được truyền vào, lấy thông tin từ texture
        if(width>0||height>0){
            dest.w=width;
            dest.h=height;
        }

        // Nếu không, truy vấn thông tin về kích thước của texture
        else SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    SDL_Texture* Graphics::loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void Graphics::blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }
