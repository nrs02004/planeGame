//
//  enemyShip.h
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__powerup__
#define __airplaneGame__powerup__

#include "weapon.h"
#include "hitbox.h"
#include "image.h"
#include <vector>
#include "color.h"

//This needs to be fixed to add life

class Powerup : public PhysicalObject{
public:
  Powerup(Weapon*, float, float, float, Image*, Color, std::vector<Hitbox>);
  bool within_bounds(float, float);
  ~Powerup();

  void update(float);

  bool used;
  float y_vel;
  std::vector<Hitbox> hitboxes;
  Weapon* weapon;
};

#endif
