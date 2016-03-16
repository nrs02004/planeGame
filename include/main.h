//
//  main.h
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef airplaneGame_main_h
#define airplaneGame_main_h

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include<vector>
#include<map>
#include"bullet.h"
#include"enemyShip.h"
#include"image.h"
#include"lua/lua.hpp"
#include"ship.h"

void init_images(lua_State *);
void init_colors(lua_State *);
void init_weapons(lua_State *);
Ship* init_ship(lua_State *);

float update_time(Uint32&, Uint32&);

void clean_up();

#endif
