#ifndef _EVENT__H
#define _EVENT__H

#include "graphics.h"

struct Event
{
    void mouse();
    void mousePress(Graphics &graphics,SDL_Texture* background=NULL);
    void keyp();
};


#endif // _EVENT__H

