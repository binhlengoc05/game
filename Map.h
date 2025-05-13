#ifndef MAP__H_
#define MAP__H_

#include <string>
#include "graphics.h"
#include "defs.h"
using namespace std;

struct Block {
    int value = 0;
    SDL_Rect rect;
};

//read map from file
bool loadMap(const string& filename, Block** blocks);

void drawMap(Graphics &graphics,Block **blocks,float cameraOffsetY);

#endif // MAP__H_
