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


Ship::Ship(float init_x, float init_y, std::vector<Image*> *ship_images) 
  : PhysicalObject(init_x, init_y, ship_images)
{
  x_vel = 0;
  y_vel = 0;
  accel = 1600;
  max_vel = 400;
  active_thrust_x = false;
  active_thrust_y = false;
  cool_down_length = 0.3;
  cool_down_timer = 0.0;
  banking = 0;
  firePort = 1;
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
    
    cool_down_timer = fmax(cool_down_timer - dt, 0.0);
    
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

void Ship::fire(std::vector<Bullet*>& bullets, Image* bullet_image)
{
    if(cool_down_timer <= 0.0f){
      Bullet *myBullet = new Bullet(x + firePort*PORTWIDTH, y, BULLETSPEEDX, BULLETSPEEDY/2, BULLETACCELY, bullet_image);
      firePort *= -1;
        bullets.push_back(myBullet);
        cool_down_timer = cool_down_length;
    }
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
