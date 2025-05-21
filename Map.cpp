#include "Map.h"
#include <fstream>

Block::Block(){
    value = 0;
    rect = {0,0,0,0};
    texture = nullptr;
}

Block::~Block() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr; // Đặt lại về nullptr để an toàn
    }
}

//read map from file
bool loadMap(const string& filename, Block** blocks) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    int row = 0;
    while (getline(file, line)) {
        for (int col = 0; col < line.length() && col < MAP_WIDTH; col++) {
            Block& b = blocks[row][col];
            b.value = 0; // Mặc định là không có khối
            if (line[col] == '1') {
                b.value = 1;
                b.rect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            }
            else if (line[col] == '3') {
                b.value = 3;
                b.rect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE-5, TILE_SIZE };
            }
            else if (line[col] == '2') {
                b.value = 2;
                b.rect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE/2 };
            }
            else if (line[col] == '4') {
                b.value = 4;
                b.rect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE/2 };
            }
        }
        row++;
        if (row == MAP_HEIGHT) break;
    }
    file.close();
    return true;
}

void drawMap(Graphics &graphics,Block **blocks,float cameraOffsetY){

        // Vẽ
        SDL_SetRenderDrawColor(graphics.renderer, 135, 206, 235, 255); // Sky blue background
        SDL_RenderClear(graphics.renderer);

        // Vẽ khối
        for (int row = 0; row < MAP_HEIGHT; ++row) {
            for (int col = 0; col < MAP_WIDTH; ++col) {
                const Block& block = blocks[row][col];
                if (block.value == 0) continue; // Bỏ qua nếu không có khối

                SDL_Rect drawRect = block.rect;
                drawRect.y -= static_cast<int>(cameraOffsetY);
                if (drawRect.y + drawRect.h >= 0 && drawRect.y <= SCREEN_HEIGHT) {
                    if (block.value == 2) { // Khối thấp
                        SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255); // white
                        SDL_RenderFillRect(graphics.renderer, &drawRect);
                    }
                    else if (block.value == 3) { // thang leo
                        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 255, 255); // Blue
                        SDL_RenderFillRect(graphics.renderer, &drawRect);
                    }
                    else if (block.value == 4) { // bậc thang
                        SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 200, 255); //yellow
                        SDL_RenderFillRect(graphics.renderer, &drawRect);
                    }
                    else { // Khối thường
                        SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255); // White
                        SDL_RenderFillRect(graphics.renderer, &drawRect);
                    }
                }
            }
        }

}
