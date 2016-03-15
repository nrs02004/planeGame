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
#include <SDL2/SDL.h>
//#include "SDL_image.h"
#include <SDL2_image/SDL_image.h>
#include "ship.h"
#include "bullet.h"
#include "enemyShip.h"
#include "image.h"
#include "physicalObject.h"
#include "color.h"

void apply_texture( int, int, int, int, SDL_Texture*, SDL_Renderer*, double, Color );
SDL_Texture* load_texture( std::string, SDL_Renderer* );
bool init(SDL_Renderer*&);
bool update_disp(SDL_Renderer*, Image*, Ship*, std::vector<Bullet*>&, std::vector<EnemyShip*>&, std::vector<Bullet*>&);
void apply_PhysicalObject(SDL_Renderer*, PhysicalObject*, int);
void apply_Ship(SDL_Renderer*, Ship*);
void apply_enemyShip(SDL_Renderer*, EnemyShip*);
void apply_Bullet(SDL_Renderer*, Bullet*);

#endif /* defined(__airplaneGame__display__) */
