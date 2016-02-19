//
//  event.h
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__level__
#define __airplaneGame__level__

#include <iostream>
#include <algorithm>
#include <functional>
#include <stack>
#include "SDL2/SDL.h"
//#include "SDL/SDL_image.h"
#include "enemyShip.h"
#include "vector"
#include "string"
#include "map"
#include "luaObj.h"
#include "lua_binding.h"
#include "lua/lua.hpp"
#include "image.h"
#include "ship.h"
#include "bullet.h"
#include "action.h"
#include "defs.h"
#include "display.h"
#include "layer.h"

class Level : public Layer
{
public:
  Level(std::string, lua_State*, std::map<std::string, Image*>, Ship* myShip) ;
  ~Level();
    
  void update(float, std::vector<Action*> &, std::stack<Layer*> &layers);
  void update_enemies(std::vector<EnemyShip*> &, float);
  void update_ship(Ship*, float);
  void load_new_enemies(std::vector<EnemyShip*> &);
  void update_bullets(std::vector<Bullet*> &, float);
  void enemy_actions(std::vector<EnemyShip*> &, std::vector<Bullet*> &);
  void check_collisions(std::vector<Bullet*> &, std::vector<EnemyShip*> &);
  bool check_collide(Bullet*, EnemyShip*);
  void apply_actions(std::vector<Action*> &,Ship*, std::vector<Bullet*> &, float, std::stack<Layer*> &);
  void display();
    
    float currComplete, speed;
    std::vector<EnemyShip*> future_enemies;
    std::map<std::string, Image*> images;

    Ship *myShip;
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> enemy_bullets;
    std::vector<EnemyShip*> enemies;
};

#endif /* defined(__airplaneGame__level__) */
