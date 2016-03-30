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
#include "powerup.h"

void apply_texture( int, int, int, int, SDL_Texture*, double, Color );
SDL_Texture* load_texture( std::string);
bool init_SDL();
bool update_disp(Image*, Ship*, std::vector<Bullet*>&, std::vector<EnemyShip*>&, std::vector<Bullet*>&, std::vector<Powerup*> &);
void apply_PhysicalObject(PhysicalObject*, int);
void apply_Ship(Ship*);
void apply_enemyShip(EnemyShip*);
void apply_Bullet(Bullet*);

#endif /* defined(__airplaneGame__display__) */
