//
//  weapon.cpp
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "powerup.h"
#include "defs.h"
#include <math.h>

Powerup::Powerup(Weapon* _weapon, float _y_vel, float _x, float _y, Image *_image, Color _color, std::vector<Hitbox> hitboxes) : PhysicalObject(_x, _y, _image, _color, hitboxes)
{
  y_vel = _y_vel;
  weapon = _weapon;

  //jostling weapon values a little bit

  weapon->portWidth *= (50.0 + float(rand() % 50)) / 75.0;
  weapon->bullet_accel_y *= (50.0 + float(rand() % 50)) / 75.0;
  weapon->bullet_init_speed_y *= (50.0 + float(rand() % 50)) / 75.0;
  weapon->cool_down_length *= (50.0 + float(rand() % 50)) / 75.0;


  used = false;

}

void Powerup::update(float dt)
{
  y += y_vel*dt;
}

bool Powerup::within_bounds(float max_y, float max_x)
{
  return (x > SCREEN_BUFFER) && (x < max_x - SCREEN_BUFFER) && (y > SCREEN_BUFFER) && (y < max_y - SCREEN_BUFFER);
}

Powerup::~Powerup()
{
}

