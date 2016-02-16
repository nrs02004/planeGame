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
#include "SDL/SDL.h"
#include "defs.h"
#include<vector>
#include "action.h"
#include "image.h"
#include "physicalObject.h"

class EnemyShip : public PhysicalObject{
public:
  EnemyShip(float, float, float, float, float, Image*);
  ~EnemyShip();
    
    void update(float dt);
    bool within_bounds(float max_y, float max_x);
    void fire(std::vector<Bullet*>& enemy_bullets, Image* bullet_image);
    void takeDmg(Bullet*);

    float speed,cool_down_length, cool_down_timer,life;
    bool firing, exploded;
};


#endif 
