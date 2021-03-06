//
//  ship.h
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__ship__
#define __airplaneGame__ship__

#include "bullet.h"
#include "SDL2/SDL.h"
#include <vector>
#include <string>
#include "image.h"
#include "physicalObject.h"
#include "weapon.h"
#include "color.h"
#include "visible_equipment.h"
//#include "enemyShip.h"

class Ship : public PhysicalObject{
public:
  Ship(float, float, std::vector<Image*> *, Color, float, float, float, std::vector<Hitbox>);
  ~Ship();

  void add_weapon(Weapon);

    void update(float dt);
    void x_thrust(float power);
    void y_thrust(float power);
    void passive_break_x(float power);
    void passive_break_y(float power);
    void fire(std::vector<Bullet*>& bullets);
    void enforce_bounds(float, float);
    void takeDmg(Bullet*);
    void add_shield(Shield);
    void use_shield();

    float x_vel,y_vel,max_vel,accel, life;
    bool active_thrust_x, active_thrust_y, exploded;
    int banking;

    Shield shield;
    std::vector<Weapon> weapons;
};

#endif /* defined(__airplaneGame__ship__) */
