
#include "player.h"

Player::Player(){
    x = SCREEN_WIDTH / 2;
    y = (MAP_HEIGHT * TILE_SIZE - SCREEN_HEIGHT) - 100;
    vx = 0;
    vy = 0;
    Fmove = 0;
    Fjump = 0;
    is_jumping = false;
    isBoy = false;
    isMan = false;
    isOld = false;
}
void Player::man(Graphics &graphics){
    texture=graphics.loadTexture("man.png");
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
    playerSrc={rect.w/4*0 , 0 , rect.w/4 , rect.h};//x,y,w,h
    rect={0 , 0 , SCREEN_WIDTH/19 , SCREEN_HEIGHT/11 };//x,y,w,h
    Fmove = 200.0f;
    Fjump = 540.0f;
}
void Player::baby(Graphics &graphics){
    texture=graphics.loadTexture("baby.png");
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
    playerSrc={rect.w/4*0 , 0 , rect.w/4 , rect.h};//x,y,w,h
    rect={0 , 0 , SCREEN_WIDTH/19 , SCREEN_HEIGHT/11 };//x,y,w,h
    Fmove = 100.0f;
    Fjump = 0;
}
void Player::boy(Graphics &graphics){
    texture=graphics.loadTexture("boy.png");
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
    playerSrc={rect.w/4*0 , 0 , rect.w/4 , rect.h};//x,y,w,h
    rect={0 , 0 , SCREEN_WIDTH/19-20 , SCREEN_HEIGHT/11 };//x,y,w,h
    Fmove = 160.0f;
    Fjump = 450.0f;
}
void Player::old(Graphics &graphics){
    texture=graphics.loadTexture("old.png");
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);// cho playerRect lưu texture player theo chieu rong va cao vao playerRect.w/h
    playerSrc={rect.w/4*0 , 0 , rect.w/4 , rect.h};//x,y,w,h
    rect={0 , 0 , SCREEN_WIDTH/19-20 , SCREEN_HEIGHT/11 };//x,y,w,h
    Fmove = 100.0f;
    Fjump = 0;
}

bool isGameOver(Player& player, float cameraOffsetY) {
    return (player.y - cameraOffsetY > SCREEN_HEIGHT + 100);
}

void handleInput(SDL_Event& event, Player& player, Block** blocks, Mix_Chunk *gJump, Graphics& graphics) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE && !player.is_jumping) {
            player.vy = -player.Fjump; // Lực nhảy -600
            if(player.Fjump>0) graphics.play(gJump);
            player.is_jumping = true;
        }
    }
}

void updatePlayer(Player& player, Block** blocks, float deltaTime, float cameraOffsetY, float scrollSpeed,Graphics &graphics, bool& quit) {
        // Áp dụng trọng lực
    const float gravity = 666.0f;//800
    player.vy += gravity * deltaTime;

    // Tính vị trí mới (chưa cập nhật ngay)
    float newX = player.x + player.vx * deltaTime;
    float newY = player.y + player.vy * deltaTime;

    // Di chuyển ngang
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    player.vx = 0;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) player.vx = - player.Fmove;//300
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) player.vx = player.Fmove;//300
    newX = player.x + player.vx * deltaTime;

    // Xử lý va chạm theo bốn góc
    bool onGround = false;

    // Tính vùng lân cận để kiểm tra khối (giảm số lần kiểm tra)
    int startRow = max(0, static_cast<int>((player.y - TILE_SIZE) / TILE_SIZE));
    int endRow = min(MAP_HEIGHT - 1, static_cast<int>((player.y + player.rect.h + TILE_SIZE) / TILE_SIZE));
    int startCol = max(0, static_cast<int>((player.x - TILE_SIZE) / TILE_SIZE));
    int endCol = min(MAP_WIDTH - 1, static_cast<int>((player.x + player.rect.w + TILE_SIZE) / TILE_SIZE));

    for (int row = startRow; row <= endRow; ++row) {
        for (int col = startCol; col <= endCol; ++col) {
            const Block& block = blocks[row][col];
            if (!block.isDraw) continue; // Bỏ qua nếu không có khối

            SDL_Rect blockRect = block.rect;
            float blockTop = blockRect.y;
            float blockBottom = blockRect.y + blockRect.h;
            float blockLeft = blockRect.x;
            float blockRight = blockRect.x + blockRect.w;

            // Tọa độ bốn góc của nhân vật ở vị trí mới
            float topLeftX = newX;
            float topLeftY = newY;
            float topRightX = newX + player.rect.w;
            float topRightY = newY;
            float bottomLeftX = newX;
            float bottomLeftY = newY + player.rect.h;
            float bottomRightX = newX + player.rect.w;
            float bottomRightY = newY + player.rect.h;

            // Va chạm dọc: Kiểm tra góc bottom-left và bottom-right khi rơi xuống
            if (player.vy >= 0 &&
                ((bottomLeftY > blockTop && player.y + player.rect.h <= blockTop) ||
                 (bottomRightY > blockTop && player.y + player.rect.h <= blockTop)) &&
                bottomLeftX < blockRight && bottomRightX > blockLeft) {
                newY = blockTop - player.rect.h; // Đặt nhân vật trên khối
                player.vy = 0;
                player.is_jumping = false;
                onGround = true;
            }
            // Va chạm dọc: Kiểm tra góc top-left và top-right khi nhảy lên
            else if (player.vy < 0 &&
                     ((topLeftY < blockBottom && player.y >= blockBottom) ||
                      (topRightY < blockBottom && player.y >= blockBottom)) &&
                     topLeftX < blockRight && topRightX > blockLeft
                     &&block.value!=4//muốn nhảy lên qua được block có value =4
                     ) {
                newY = blockBottom; // Đặt nhân vật dưới khối
                player.vy = 0;
            }

            // Va chạm ngang: Kiểm tra góc top-right và bottom-right khi di chuyển phải
            if (player.vx > 0 &&
                ((topRightX > blockLeft && player.x + player.rect.w <= blockLeft) ||
                 (bottomRightX > blockLeft && player.x + player.rect.w <= blockLeft)) &&
                topRightY < blockBottom && bottomRightY > blockTop
                &&block.value!=4//muốn nhảy ngang được block có value =4
                ) {
                newX = blockLeft - player.rect.w; // Đặt nhân vật sát cạnh trái khối
                player.vx = 0;
            }
            // Va chạm ngang: Kiểm tra góc top-left và bottom-left khi di chuyển trái
            else if (player.vx < 0 &&
                     ((topLeftX < blockRight && player.x >= blockRight) ||
                      (bottomLeftX < blockRight && player.x >= blockRight)) &&
                     topLeftY < blockBottom && bottomLeftY > blockTop
                     &&block.value!=4//muốn nhảy ngang qua được block có value =4
                     ) {
                newX = blockRight; // Đặt nhân vật sát cạnh phải khối
                player.vx = 0;
            }
        }
    }

    // Cập nhật vị trí nhân vật
    player.x = newX;
    player.y = newY;

    int tileX = static_cast<int>(newX) / TILE_SIZE;
    int tileY = static_cast<int>(newY) / TILE_SIZE;
    if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
        int blockValue = blocks[tileY][tileX].value;
        if (blockValue == NUMBER_BOY && !player.isBoy) {
            player.isBoy = true;
            player.boy(graphics);
        }
        else if (blockValue == NUMBER_MAN && !player.isMan) {
            player.isMan = true;
            player.man(graphics);
        }
        else if (blockValue == NUMBER_OLD && !player.isOld) {
            player.isOld = true;
            player.old(graphics);
        }
        else if(blockValue == NUMBER_END){
            quit=true;
        }
    }
    // Nếu đứng trên khối, di chuyển lên theo map
    if (onGround) {
        player.y -= scrollSpeed * deltaTime;
    }
}

void drawPlayer(Player player,Graphics &graphics,float cameraOffsetY){

        player.rect.x = static_cast<int>(player.x);
        player.rect.y = static_cast<int>(player.y - cameraOffsetY);
        SDL_RenderCopy(graphics.renderer,player.texture,&player.playerSrc,&player.rect);
}
