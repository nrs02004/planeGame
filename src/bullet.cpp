//
//  bullet.cpp
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "bullet.h"
#include "defs.h"
#include<iostream>

Bullet::Bullet(float init_x, float init_y, float init_vel_x, float init_vel_y, float init_accel_y, Image* init_bullet_image)
  : PhysicalObject(init_x, init_y, init_bullet_image)
{
    x_vel = init_vel_x;
    y_vel = init_vel_y;
    y_accel = init_accel_y;
    exploded = 0;
    damage = 30;
}

void Bullet::update(float dt)
{
  x += x_vel*dt;
  y -= y_vel*dt;
  y_vel += y_accel*dt;
}

bool Bullet::within_bounds(float max_y, float max_x)
{
  return (x > SCREEN_BUFFER) && (x < max_x - SCREEN_BUFFER) && (y > SCREEN_BUFFER) && (y < max_y - SCREEN_BUFFER);
}

void Bullet::explode()
{
  exploded = 1;
}

Bullet::~Bullet()
{
}
