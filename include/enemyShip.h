//
//  enemyShip.h
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__enemyShip__
#define __airplaneGame__enemyShip__

#include <iostream> 
#include "SDL2/SDL.h"
#include "defs.h"
#include<vector>
#include "action.h"
#include "image.h"
#include "physicalObject.h"
#include "color.h"
#include "hitbox.h"
#include "weapon.h"

class EnemyShip : public PhysicalObject{
public:
  EnemyShip(float, float, float, float, float, Image*, Color, std::vector<Hitbox>);
  ~EnemyShip();

  void add_weapon(Weapon*);
    void update(float dt);
    bool within_bounds(float max_y, float max_x);
    void fire(std::vector<Bullet*>& enemy_bullets);
    void takeDmg(Bullet*);

    float speed, life;
    bool exploded;
    std::vector<Hitbox> hitboxes;
    std::vector<Weapon> weapons;
};


#endif 
