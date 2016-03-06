//
//  display.h
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__display__
#define __airplaneGame__display__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "SDL2/SDL.h"
//#include "SDL_image.h"
#include "SDL2_image/SDL_image.h"
#include "ship.h"
#include "bullet.h"
#include "enemyShip.h"
#include "image.h"
#include "physicalObject.h"

void apply_surface( int, int, SDL_Surface*, SDL_Surface* );
SDL_Surface *load_image( std::string, SDL_Surface* );
bool init(SDL_Surface*&);
bool update_disp(SDL_Surface*, SDL_Surface*, Ship*, std::vector<Bullet*>&, std::vector<EnemyShip*>&, std::vector<Bullet*>&);
void apply_PhysicalObject(SDL_Surface*, PhysicalObject*, int);
void apply_Ship(SDL_Surface*, Ship*);
void apply_enemyShip(SDL_Surface*, EnemyShip*);
void apply_Bullet(SDL_Surface*, Bullet*);

#endif /* defined(__airplaneGame__display__) */
