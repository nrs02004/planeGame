#ifndef airplaneGame_global_h

#define airplaneGame_global_h

#include "SDL2/SDL.h"
#include "color.h"
#include "weapon.h"

extern SDL_Window* gWindow; //setting the window globally
extern SDL_Renderer* renderer;
extern std::map<std::string, Color*> colors;
extern std::map<std::string, Weapon*> weapon_list;
extern std::map<std::string, Image*> images;

//extern SDL_Renderer* gRenderer;


#endif
