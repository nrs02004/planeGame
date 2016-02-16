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

void enemy_actions(std::vector<EnemyShip*> &, std::vector<Bullet*> &, Image*);
void createEnemies(std::vector<EnemyShip*> &, Image*, lua_State*);
float update_time(Uint32&, Uint32&);
void update_ship(Ship *, float);
void update_enemies(std::vector<EnemyShip*> &, float);
void update_bullets(std::vector<Bullet*> &, float);
void apply_actions(std::vector<Action*> &actions,Ship* myShip, std::vector<Bullet*> &bullets, Image* bullet_image, float dt);
void check_collisions(std::vector<Bullet*>&, std::vector<EnemyShip*>&);
bool check_collide(Bullet*, EnemyShip*);
void clean_up(std::map<std::string, Image*> &);

#endif
