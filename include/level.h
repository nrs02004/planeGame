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
#include <map>
#include <stack>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
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
#include "color.h"
#include "weapon.h"
#include "powerup.h"

class Level : public Layer
{
public:
  Level(std::string, lua_State*, Ship*) ;
  ~Level();

  void update(float, std::vector<Action*> &, std::stack<Layer*> &layers);
  void update_enemies(std::vector<EnemyShip*> &, std::vector<Powerup*> &, float);
  void update_ship(Ship*, float);
    void update_powerups(std::vector<Powerup*> &, float);
  void load_enemies_from_file(lua_State *, std::vector<EnemyShip*> &);
  void load_new_enemies(std::vector<EnemyShip*> &);
  void update_bullets(std::vector<Bullet*> &, float);
  void enemy_actions(std::vector<EnemyShip*> &, std::vector<Bullet*> &);
  void check_collisions(std::vector<Bullet*> &, std::vector<EnemyShip*> &);
  void check_ship_collisions(Ship*, std::vector<Bullet*> &, std::vector<Powerup*> &);
  void check_ship_ship_collisions(Ship*, std::vector<EnemyShip*> &);
  bool check_collide(PhysicalObject*, PhysicalObject*);
    void roll_powerup(std::vector<Powerup*> &, EnemyShip*);
  void apply_actions(std::vector<Action*> &,Ship*, std::vector<Bullet*> &, float, std::stack<Layer*> &);
  void display();

    float currComplete, speed;
    std::vector<EnemyShip*> future_enemies;

    Ship *myShip;
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> enemy_bullets;
    std::vector<EnemyShip*> enemies;
    std::vector<Powerup*> powerups;
    std::map<std::string, Weapon*> powerup_weapons;
};

#endif /* defined(__airplaneGame__level__) */
