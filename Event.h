#ifndef _EVENT__H
#define _EVENT__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

struct Event
{
    void mouse();
    void mousePress(Graphics &graphics);
    void keyp();
};


#endif // _EVENT__H

