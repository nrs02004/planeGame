//
//  event.cpp
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include <algorithm>
#include <functional>
#include "level.h"
#include "enemyShip.h"
#include "luaObj.h"
#include "lua_binding.h"
#include "lua/lua.hpp"
#include "defs.h"
#include "globals.h"


bool cmp( const EnemyShip *s1, const EnemyShip *s2 ){return (s1)->y < (s2)->y;}

Level::Level(std::string filename, lua_State *L, Ship* _myShip) : Layer()
{
  currComplete = 0;
  speed = 100;

  load_file(L, filename);

  myShip = _myShip;
  myShip->x = 500; myShip->y = 680;

  // Loading the enemy ships (REALLY LOADING LEVEL)
  load_enemies_from_file(L, future_enemies);

  //clean up things
}

//should probably change SCREEN_HEIGHT here
void Level::update(float dt, std::vector<Action*> &actions, std::stack<Layer*> &layers)
{
  //Updating where in the level we are
  currComplete += speed * dt;

  //Update enemies currently on screen
  load_new_enemies(enemies);

  //Updating our ship
  update_ship(myShip, dt);

  //Updating enemy ships
  update_enemies(enemies, powerups, dt);

    //Updating powerups
    update_powerups(powerups, dt);

  //"apply enemy actions"
  enemy_actions(enemies, enemy_bullets);

  //Updating the bullets
  update_bullets(bullets, dt);
  update_bullets(enemy_bullets, dt);

  //Checking for bullet --- enemy ship collisions
  check_collisions(bullets, enemies);

  //Checking for enemy bullet --- myShip collisions
  check_ship_collisions(myShip, enemy_bullets, powerups);

  apply_actions(actions, myShip, bullets, dt, layers);

    if(myShip->exploded == true) {terminate = true;}
}

void Level::display()
{
  update_disp(images["background"], myShip, bullets, enemies, enemy_bullets, powerups);
}

void Level::load_enemies_from_file(lua_State *L, std::vector<EnemyShip*> &future_enemies)
{
  std::string enemy_data = "enemy_stack";
  std::vector<Ship_dat*> ship_dat = lua_get_ships(L, enemy_data);

  for(auto shipIt = ship_dat.begin(); shipIt != ship_dat.end(); shipIt++){
    EnemyShip *newEnemy = new EnemyShip((*shipIt)->x, (*shipIt)->y,
					(*shipIt)->speed,(*shipIt)->cool_down_length,
					(*shipIt)->life, images[(*shipIt)->name],
					*colors[(*shipIt)->color],
					(*shipIt)->hitboxes);
    newEnemy->add_weapon(weapon_list[(*shipIt)->weapon_name]);
    future_enemies.push_back(newEnemy);
    delete(*shipIt);

  }
  // Sort the  ships by y-value

  std::sort(future_enemies.begin(), future_enemies.end(),cmp);

    std::string powerup_weapon_data = "powerup_weapons";
    std::vector<std::string> powerup_weapon_names = lua_get_string_vec(L, powerup_weapon_data);

    for(auto wIt = powerup_weapon_names.begin(); wIt != powerup_weapon_names.end(); wIt++){
        powerup_weapons[*wIt] = weapon_list[*wIt];
    }

}

void Level::load_new_enemies(std::vector<EnemyShip*> &enemies)
{
  if(!future_enemies.empty()){

    for(auto it = future_enemies.begin();
	((*it)->y - currComplete <= SCREEN_HEIGHT) &&
	  (it != future_enemies.end());){

      (*it)->y = SCREEN_HEIGHT + SCREEN_BUFFER - ((*it)->y - currComplete);
      enemies.push_back(*it);
      it = future_enemies.erase(it);
    }
  }
}

void Level::update_bullets(std::vector<Bullet*> &bullets, float dt)
{

    if(!bullets.empty())
    {
        for(std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();){
	  (*it)->update(dt);
	  if(((*it)->within_bounds(SCREEN_HEIGHT, SCREEN_WIDTH) == false) ||
	     ((*it)->exploded))
	    {
	      it = bullets.erase(it);
	    }
	  else
	    {
	      it++;
	    }

        }
    }
}

void Level::enemy_actions(std::vector<EnemyShip*> &enemies, std::vector<Bullet*> &enemy_bullets)
{
  if(!enemies.empty())
    {
      for(std::vector<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end();it++){
	(*it)->fire(enemy_bullets);
      }
    }
}


void Level::update_ship(Ship* myShip, float dt)
{
  myShip->update(dt);
  myShip->enforce_bounds(SCREEN_HEIGHT, SCREEN_WIDTH);
}

void Level::update_powerups(std::vector<Powerup*> &powerups, float dt)
{
    if(!powerups.empty())
    {
        for(auto it = powerups.begin(); it != powerups.end();){

            (*it)->update(dt);

            if(((*it)->within_bounds(SCREEN_HEIGHT, SCREEN_WIDTH) == false) ||
               ((*it)->used == true))
            {
                delete *it;
                it = powerups.erase(it);
            }
            else{
                it++;
            }
        }
    }
}

void Level::update_enemies(std::vector<EnemyShip*> &enemies, std::vector<Powerup*> &powerups, float dt)
{
    if(!enemies.empty())
    {
        for(std::vector<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end();){
	  (*it)->update(dt);

	  if(((*it)->within_bounds(SCREEN_HEIGHT, SCREEN_WIDTH) == false))
      {
          delete *it;
          it = enemies.erase(it);
      }
      else
        {
          if((*it)->exploded == true)
          {
              roll_powerup(powerups, (*it));
              delete *it;
              it = enemies.erase(it);
          }
          else
          {
              it++;
          }
        }

        }
    }
}

void Level::check_collisions(std::vector<Bullet*> &bullets, std::vector<EnemyShip*> &ships)
{
  if(!bullets.empty()){
    for(std::vector<Bullet*>::iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++){
      if(!ships.empty()){
	for(std::vector<EnemyShip*>::iterator shipIt = ships.begin(); shipIt != ships.end(); shipIt++){
	  if(check_collide(*bulletIt, *shipIt)){
	    (*shipIt)->takeDmg(*bulletIt);
	    (*bulletIt)->explode();
	    break;
	  }
	}
      }
    }
  }
}


void Level::check_ship_collisions(Ship *myShip, std::vector<Bullet*> &bullets, std::vector<Powerup*> &powerups)
{
  if(!bullets.empty()){
    for(std::vector<Bullet*>::iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++){
      if(check_collide(*bulletIt, myShip)){
	    myShip->takeDmg(*bulletIt);
	    (*bulletIt)->explode();
	break;
      }
    }
  }
    if(!powerups.empty()){
        for(auto powerupIt = powerups.begin(); powerupIt != powerups.end(); powerupIt++){
            if(check_collide(*powerupIt, myShip)){
                myShip->add_weapon((*powerupIt)->weapon);
                (*powerupIt)->used = true;
            }
        }
    }
}



void Level::apply_actions(std::vector<Action*> &actions,Ship* myShip, std::vector<Bullet*> &bullets, float dt, std::stack<Layer*> &layers)
{
    myShip->active_thrust_x = false;
    myShip->active_thrust_y = false;
    if(!actions.empty())
    {
        for(std::vector<Action*>::iterator it = actions.begin(); it != actions.end(); it++){
            switch((*it)->action_type){
                case THRUST:
                    (*it)->apply(myShip, dt);
                    break;
                case FIRE:
                    (*it)->apply(myShip, dt, bullets);
                    break;
                case CLICK:
                    (*it)->apply();
		    pause_layer* new_pause = new pause_layer();
                    layers.push(new_pause);
            }
        }
    }
    actions.clear();
}

bool Level::check_collide(PhysicalObject *obj1, PhysicalObject *obj2)
{
  for(auto hitBoxIt1 = obj1->hitboxes.begin(); hitBoxIt1 != obj1->hitboxes.end(); hitBoxIt1++){
    for(auto hitBoxIt2 = obj2->hitboxes.begin(); hitBoxIt2 != obj2->hitboxes.end(); hitBoxIt2++){
      float x_dist = ( obj1->x + hitBoxIt1->x ) - ( obj2->x + hitBoxIt2->x );
      float y_dist = ( obj1->y + hitBoxIt1->y ) - ( obj2->y + hitBoxIt2->y );
      float dist = sqrt(pow(x_dist,2) + pow(y_dist,2));
      if(dist <= ( hitBoxIt1->r + hitBoxIt2->r )){
      return true;
      }
    }
  }
  return false;
}

void Level::roll_powerup(std::vector<Powerup*> &powerups, EnemyShip* enemyship)
{
    if( rand() % 1000 > 900 ){
        auto weapon_it = powerup_weapons.begin();
        std::advance(weapon_it, rand() % powerup_weapons.size());

        //This should maybe be elsewhere?
        std::vector<Hitbox> hitboxes;
        hitboxes.push_back(Hitbox(0,0,14));

	        Powerup* new_powerup = new Powerup((weapon_it->second), 200.0 + rand() % 200, enemyship->x, enemyship->y,
                                           images["powerup"], (weapon_it->second)->color, hitboxes );
					   powerups.push_back(new_powerup);
    }
}

Level::~Level()
{
   bullets.clear(); enemies.clear(); enemy_bullets.clear();
}
