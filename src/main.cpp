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
	  Level1->update_ship(myShip, dt);
        
	  //Updating enemy ships
	  Level1->update_enemies(enemies, dt);
	  
	  //"apply enemy actions"
	  Level1->enemy_actions(enemies, enemy_bullets, images["bullet_image"]);
	  
	  //Updating the bullets
	  Level1->update_bullets(bullets, dt);
	  Level1->update_bullets(enemy_bullets, dt);
	  
	  //Checking for bullet --- ship collisions
	  Level1->check_collisions(bullets, enemies);
	  
	  //Checking for key presses
	  handle_event(event, quit, actions);
	  
	  Level1->apply_actions(actions, myShip, bullets, images["bullet_image"], dt);
	  
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

// This function updates the change in time: dt
float update_time(Uint32 &old_time, Uint32 &current_time)
{
    old_time = current_time;
    current_time = SDL_GetTicks();
    return (current_time - old_time) / 1000.0f;
    
}
