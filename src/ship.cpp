//
//  ship.cpp
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "ship.h"
#include "defs.h"
#include <math.h>


Ship::Ship(float init_x, float init_y, std::vector<Image*> *ship_images, Color _color, float _accel, float _max_vel, float _life, std::vector<Hitbox> _hitboxes)
  : PhysicalObject(init_x, init_y, ship_images, _color, _hitboxes)
{
  x_vel = 0;
  y_vel = 0;
  accel = _accel;
  max_vel = _max_vel;
  active_thrust_x = false;
  active_thrust_y = false;
  banking = 0;
  life = _life;
  exploded = 0;
}

void Ship::add_weapon(Weapon* weapon)
{
  weapons.push_back(weapon);
}

void Ship::update(float dt)
{
    x = x + x_vel * dt;
    y = y + y_vel * dt;

    if(active_thrust_x == false){
        passive_break_x(dt * accel/2);
	banking = 0;
    }
    if(active_thrust_y == false){
        passive_break_y(dt * accel/2);
    }
    
    active_thrust_x = false;
    active_thrust_y = false;

  for(auto weapon_it = weapons.begin(); weapon_it != weapons.end(); weapon_it++){
    (*weapon_it)->update(dt);
  }

    if(life <= 0.0){exploded = true;}

}

void Ship::x_thrust(float power)
{
    x_vel = x_vel + power;
    x_vel = copysignf(1.0, x_vel) * fmin(max_vel, fabs(x_vel)); //stops you from exceeding max_vel
    active_thrust_x = true;
    if(power < 0)
      {
	if(x_vel > -max_vel){ banking = -1;}
	else{ banking = -2;}
      }
    if(power > 0)
      {
	if(x_vel < max_vel) {banking = 1;}
	else {banking = 2;}
      }
}

void Ship::y_thrust(float power)
{
    y_vel = y_vel + power;
    y_vel = copysignf(1.0, y_vel) * fmin(max_vel, fabs(y_vel)); //stops you from exceeding max_vel
    active_thrust_y = true;
}

// Break is applied if you are not accelerating in x direction

void Ship::passive_break_x(float power)
{
    x_vel = copysignf(1.0, x_vel) * fmax(fabs(x_vel) - power, 0); //decreases x_velocity by power, but doesn't cross 0
}

// Break is applied if you are not accelerating in y direction

void Ship::passive_break_y(float power)
{
    y_vel = copysignf(1.0, y_vel) * fmax(fabs(y_vel) - power, 0); //decreases x_velocity by power, but doesn't cross 0
}

void Ship::fire(std::vector<Bullet*>& bullets)
{

  for(auto weapon_it = weapons.begin(); weapon_it != weapons.end(); weapon_it++){
    (*weapon_it)->fire(bullets, x, y);
  }
}

void Ship::takeDmg(Bullet *bulletIt)
{
    life = life - bulletIt->damage;
}

void Ship::enforce_bounds(float max_y, float max_x)
{
  if(x < (*my_images)[0]->width/2 + SCREEN_BUFFER){ x = (*my_images)[0]->width/2 + SCREEN_BUFFER; x_vel = 0;}
  if(y < (*my_images)[0]->height/2 + SCREEN_BUFFER){ y = (*my_images)[0]->height/2 + SCREEN_BUFFER; y_vel = 0;}
  if(x > max_x - (*my_images)[0]->width/2 - SCREEN_BUFFER){ x = max_x - (*my_images)[0]->width/2 - SCREEN_BUFFER; x_vel = 0; }
  if(y > max_y - (*my_images)[0]->height/2 - SCREEN_BUFFER){ y = max_y - (*my_images)[0]->height/2 - SCREEN_BUFFER; y_vel = 0; }

}

Ship::~Ship()
{
}
