#ifndef airplaneGame_global_h

#define airplaneGame_global_h

#include "SDL2/SDL.h"
#include "color.h"

extern SDL_Window* gWindow; //setting the window globally
extern   std::map<std::string, Color*> colors;
//extern SDL_Renderer* gRenderer;


#endif
