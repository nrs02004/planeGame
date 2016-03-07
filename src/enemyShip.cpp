//
//  enemyShip.cpp
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "enemyShip.h"
#include <math.h>

EnemyShip::EnemyShip(float init_x, float init_y, float _speed, float _cool_down_length, float _life, Image* init_enemy_image)
  : PhysicalObject(init_x, init_y, init_enemy_image)
{
  speed = _speed;
  cool_down_length = _cool_down_length;
  cool_down_timer = 0.0;
  firing = false;
  life = _life;
  exploded = 0;

}

void EnemyShip::update(float dt)
{
  y += speed*dt;

  cool_down_timer = fmax(cool_down_timer - dt, 0.0);
  if(cool_down_timer <= 0.0){firing = true;}
  if(life <= 0.0){exploded = true;}
}

bool EnemyShip::within_bounds(float max_y, float max_x)
{
  return (x > SCREEN_BUFFER) && (x < max_x - SCREEN_BUFFER) && (y > SCREEN_BUFFER) && (y < max_y - SCREEN_BUFFER);
}

void EnemyShip::fire(std::vector<Bullet*>& enemy_bullets, Image* bullet_image)
{
  Bullet *myBullet = new Bullet(x, y, BULLETSPEEDX, -BULLETSPEEDY, 0, bullet_image);

  (*((PhysicalObject*)myBullet)->my_images)[0]->angle = 180; // flipping the bullet
  enemy_bullets.push_back(myBullet);
  cool_down_timer = cool_down_length;
  firing = false;
}

void EnemyShip::takeDmg(Bullet *bulletIt)
{
  life = life - bulletIt->damage;
}

EnemyShip::~EnemyShip()
{
}
