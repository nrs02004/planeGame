//
//  weapon.cpp
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "weapon.h"
#include "defs.h"
#include <math.h>

Weapon::Weapon(int _alternate, float _portWidth, float _cool_down_length,
	       float _bullet_accel_x, float _bullet_accel_y, float _bullet_init_speed_x, float _bullet_init_speed_y,
	       float _bullet_dmg, Image* _bullet_image, Color _color, std::vector<Hitbox> _hitboxes){

  firePort = 1;
  alternate = _alternate;
  portWidth = _portWidth;
  cool_down_length = _cool_down_length;
  cool_down_timer = 0.0;
  bullet_accel_x = _bullet_accel_x;
  bullet_accel_y = _bullet_accel_y;
  bullet_init_speed_x = _bullet_init_speed_x;
  bullet_init_speed_y = _bullet_init_speed_y;
  bullet_dmg = _bullet_dmg;
  bullet_image = _bullet_image;
  color = _color;
  hitboxes = _hitboxes;
  angle = 0.0;
}

void Weapon::update(float dt)
{    
    cool_down_timer = fmax(cool_down_timer - dt, 0.0);   
}

void Weapon::fire(std::vector<Bullet*>& bullets, float x, float y)
{
  if(cool_down_timer <= 0.0f){ 
    if(alternate == 2){ // DOUBLE FIRING
	Bullet *myBullet1 = new Bullet(x + portWidth, y, bullet_init_speed_x, bullet_init_speed_y, bullet_accel_y, bullet_dmg, bullet_image, color, hitboxes);
	Bullet *myBullet2 = new Bullet(x - portWidth, y, -bullet_init_speed_x, bullet_init_speed_y, bullet_accel_y, bullet_dmg, bullet_image, color, hitboxes);
	myBullet1->angle = angle;
	myBullet2->angle = angle;
        bullets.push_back(myBullet1);
	bullets.push_back(myBullet2);
        cool_down_timer = cool_down_length;
    }
    else{ // SINGLE FIRING
	Bullet *myBullet = new Bullet(x + firePort*portWidth, y, bullet_init_speed_x * firePort, bullet_init_speed_y, bullet_accel_y, bullet_dmg, bullet_image, color, hitboxes);
	myBullet->angle = angle;
	firePort *= alternate;
        bullets.push_back(myBullet);
        cool_down_timer = cool_down_length;
      }
    }
}


Weapon::~Weapon()
{
}
