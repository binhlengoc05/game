#ifndef _EVENT__H
#define _EVENT__H

#include "graphics.h"
#include "texture.h"


// Check if mouse is inside a rectangle
bool isMouseInsideRect(int mouseX, int mouseY, SDL_Rect rect);

void StartBackground(Graphics& graphics, int currentScreen, SDL_Event event_mouse, Start start, Tutorial tutorial);
void EndBackground(Graphics& graphics, SDL_Event event_mouse, Endgame endgame, bool& running_game);

#endif // _EVENT__H

