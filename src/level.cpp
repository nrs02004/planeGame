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

bool cmp( const EnemyShip *s1, const EnemyShip *s2 ){return (s1)->y < (s2)->y;}

Level::Level(std::string filename, lua_State *L, std::map<std::string, Image*> _images)
{
  currComplete = 0;
  speed = 100;
  images = _images;
  
  load_file(L, filename);

  /* std::vector<Bullet*> bullets;
  std::vector<Bullet*> enemy_bullets;
  std::vector<Action*> actions;
  std::vector<EnemyShip*> enemies;*/

  


  

  // Loading the enemy ships
  
  std::string enemy_data = "enemy_stack";
  std::vector<Ship_dat*> ship_dat = lua_get_ships(L, enemy_data);
  
  for(auto shipIt = ship_dat.begin(); shipIt != ship_dat.end(); shipIt++){
    EnemyShip *newEnemy = new EnemyShip((*shipIt)->x, (*shipIt)->y,
					(*shipIt)->speed,(*shipIt)->cool_down_length,
					(*shipIt)->life, images["enemy_image"]);
    future_enemies.push_back(newEnemy);
    delete(*shipIt);
  }
    
  // Sort the  ships by y-value
    
  std::sort(future_enemies.begin(), future_enemies.end(),cmp);
    
  //clean up things
}

//should probably change SCREEN_HEIGHT here
void Level::update(float dt, std::vector<EnemyShip*> &enemies)
{
  currComplete += speed * dt;
  
  //Should update this to pop from the back

  load_new_enemies(enemies);

  /*

  // REST OF THE UPDATE

  //Updating our ship
  update_ship(myShip, dt);
  
  //Updating enemy ships
  update_enemies(enemies, dt);
  
  //"apply enemy actions"
  enemy_actions(enemies, enemy_bullets, images["bullet_image"]);
  
  //Updating the bullets
  update_bullets(bullets, dt);
  update_bullets(enemy_bullets, dt);
  
  //Checking for bullet --- ship collisions
  check_collisions(bullets, enemies);
  
  apply_actions(actions, myShip, bullets, images["bullet_image"], dt);
  
  if(update_disp(images["screen"]->image, images["background"]->image, myShip, bullets, enemies, enemy_bullets) == -1)
    {
      return 1;
    }*/
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

void Level::enemy_actions(std::vector<EnemyShip*> &enemies, std::vector<Bullet*> &enemy_bullets, Image* bullet_image)
{
  if(!enemies.empty())
    {
      for(std::vector<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end();it++){
	if((*it)->firing == true)
	  {
	    (*it)->fire(enemy_bullets, bullet_image);
	  }
      }
    }
}


void Level::update_ship(Ship* myShip, float dt)
{
  myShip->update(dt);
  myShip->enforce_bounds(SCREEN_HEIGHT, SCREEN_WIDTH);
}


void Level::update_enemies(std::vector<EnemyShip*> &enemies, float dt)
{
    if(!enemies.empty())
    {
        for(std::vector<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end();){
	  (*it)->update(dt);

	  if(((*it)->within_bounds(SCREEN_HEIGHT, SCREEN_WIDTH) == false) ||
	     ((*it)->exploded == true))
	    {
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


void Level::apply_actions(std::vector<Action*> &actions,Ship* myShip, std::vector<Bullet*> &bullets, Image* bullet_image, float dt)
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
                    (*it)->apply(myShip, dt, bullets, bullet_image); 
                    break;
            }
        }
    }
    actions.clear();
}


bool Level::check_collide(Bullet *bullet, EnemyShip *ship)
{
  float x_dist = ship->x - bullet->x;
  float y_dist = ship->y - bullet->y;
  float dist = sqrt(pow(x_dist,2) + pow(y_dist,2));
  return (dist < COLLISION_DIST);
}


Level::~Level()
{
}
