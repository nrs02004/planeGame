//
//  main.cpp
//  airplaneGame
//
//  Created by noah simon on 10/7/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>


#include "SDL2/SDL.h"
//#include "SDL/SDL_image.h"
#include <math.h>
#include "display.h"
#include "event.h"
#include "defs.h"
#include "ship.h"
#include "main.h"
#include "bullet.h"
#include "action.h"
#include "image.h"
#include "globals.h"
#include "luaObj.h"
#include "lua_binding.h"
#include "lua/lua.hpp"
#include "level.h"

SDL_Window* gWindow = NULL;

int main( int argc, char* args[] )
{

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  
  std::map<std::string, Image*> images;

  images["background"] = new Image(NULL, 0, 0);
  images["ship_image"] = new Image(NULL, 94, 100);
  images["ship_imageR"] = new Image(NULL, 94, 100);
  images["ship_imageL"] = new Image(NULL, 94, 100);
  images["ship_imageRR"] = new Image(NULL, 94, 100);
  images["ship_imageLL"] = new Image(NULL, 94, 100);
  images["screen"] = new Image(NULL, 0, 0);
  images["bullet_image"] = new Image(NULL, 20, 40);
  images["enemy_image"] = new Image(NULL, 71, 77);

    SDL_Event event;
    
    Uint32 old_time, current_time;
    float dt;
    current_time = SDL_GetTicks();

    //Quit flag
    bool quit = false;
    
    //Initialize
    if( init(images["screen"]->image) == false )
    {
        return 1;
    }
   
    
    //Load the files
    if( load_files(images) == false )
    {
        return 1;
    }
    
    std::vector<Image*> ship_images;
    ship_images.push_back(images["ship_image"]);
    ship_images.push_back(images["ship_imageL"]);
    ship_images.push_back(images["ship_imageR"]);
    ship_images.push_back(images["ship_imageLL"]);
    ship_images.push_back(images["ship_imageRR"]);

    Ship *myShip = new Ship(240, 190, &ship_images);
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> enemy_bullets;
    std::vector<Action*> actions;
    std::vector<EnemyShip*> enemies;

    //    createEnemies(enemies, images["enemy_image"], L);

    std::string filename="level/level1.lua";
    Level* Level1 = new Level(filename, L, images);

    srand(time(0));

    current_time = SDL_GetTicks();
    //While the user hasn't quit
      while( quit == false )
	{
	  //Finding how much time has passed
	  dt = update_time(old_time, current_time);
	  
	  Level1->update(dt, enemies);
	  
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
	  
	  //Checking for key presses
	  handle_event(event, quit, actions);
	  
	  apply_actions(actions, myShip, bullets, images["bullet_image"], dt);
	  
	  if(update_disp(images["screen"]->image, images["background"]->image, myShip, bullets, enemies, enemy_bullets) == -1)
	    {
	    return 1;
	    }
	  
	}
      
    
    //Free the surfaces and quit SDL
    delete myShip;  bullets.clear(); enemies.clear(); enemy_bullets.clear();
    
    clean_up(images);
    
    return 0;
}

void clean_up(std::map<std::string, Image*> &images)
{
  // CLEAN UP IMAGES
  for(std::map<std::string, Image*>::iterator imageIt = images.begin(); imageIt != images.end(); imageIt++){
    delete (imageIt->second);
  }
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  SDL_Quit();
}

void check_collisions(std::vector<Bullet*> &bullets, std::vector<EnemyShip*> &ships)
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

bool check_collide(Bullet *bullet, EnemyShip *ship)
{
  float x_dist = ship->x - bullet->x;
  float y_dist = ship->y - bullet->y;
  float dist = sqrt(pow(x_dist,2) + pow(y_dist,2));
  return (dist < COLLISION_DIST);
}

// Reads the enemy information from "level1" file

/*void createEnemies(std::vector<EnemyShip*> &enemies, Image *enemy_image, lua_State *L)
{
  std::string filename="level/level1.lua";
  load_file(L, filename);

  std::string enemy_data = "enemy_stack";
  std::vector<Ship_dat*> ship_dat = lua_get_ships(L, enemy_data);

  for(auto shipIt = ship_dat.begin(); shipIt != ship_dat.end(); shipIt++){
    EnemyShip *newEnemy = new EnemyShip((*shipIt)->x, (*shipIt)->y, enemy_image);
    enemies.push_back(newEnemy);

    delete(*shipIt);
    }
    }*/

// This function updates the change in time: dt
float update_time(Uint32 &old_time, Uint32 &current_time)
{
    old_time = current_time;
    current_time = SDL_GetTicks();
    return (current_time - old_time) / 1000.0f;
    
}

// This function updates the ship and makes sure it stays in bounds
void update_ship(Ship* myShip, float dt)
{
  myShip->update(dt);
  myShip->enforce_bounds(SCREEN_HEIGHT, SCREEN_WIDTH);
}


// This function iterates through all the enemy ships and updates them
void update_enemies(std::vector<EnemyShip*> &enemies, float dt)
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

void enemy_actions(std::vector<EnemyShip*> &enemies, std::vector<Bullet*> &enemy_bullets, Image* bullet_image)
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

// This function iterates through all our bullets and updates them
void update_bullets(std::vector<Bullet*> &bullets, float dt)
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

// This functions iterates through the "actions" vector and applies all the actions to our ship

void apply_actions(std::vector<Action*> &actions,Ship* myShip, std::vector<Bullet*> &bullets, Image* bullet_image, float dt)
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

