//
//  enemyShip.cpp
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "enemyShip.h"
#include <math.h>

EnemyShip::EnemyShip(float init_x, float init_y, float _speed, float _cool_down_length, float _life, Image* init_enemy_image, Color _color, std::vector<Hitbox> _hitboxes)
  : PhysicalObject(init_x, init_y, init_enemy_image, _color, _hitboxes)
{
  speed = _speed;
  life = _life;
  exploded = 0;
}

void EnemyShip::add_weapon(Weapon* weapon)
{
  Weapon new_weapon = *weapon;
  new_weapon.bullet_init_speed_y *= -1;
  new_weapon.bullet_accel_y *= -1;
  new_weapon.angle = 180.0;
  weapons.push_back(new_weapon);
}

void EnemyShip::update(float dt)
{
  y += speed*dt;

  for(auto weapon_it = weapons.begin(); weapon_it != weapons.end(); weapon_it++){
    weapon_it->update(dt);
  }
    
  if(life <= 0.0){exploded = true;}
}

bool EnemyShip::within_bounds(float max_y, float max_x)
{
  return (x > SCREEN_BUFFER) && (x < max_x - SCREEN_BUFFER) && (y > SCREEN_BUFFER) && (y < max_y - SCREEN_BUFFER);
}

void EnemyShip::fire(std::vector<Bullet*>& enemy_bullets)
{
  for(auto weapon_it = weapons.begin(); weapon_it != weapons.end(); weapon_it++){
    weapon_it->fire(enemy_bullets, x, y);
  }
}

void EnemyShip::takeDmg(Bullet *bulletIt)
{
  //  std::cout << "bullet dmg: " << bulletIt->damage << "life: " << life << "\n";
  life = life - bulletIt->damage;
}

EnemyShip::~EnemyShip()
{
}
