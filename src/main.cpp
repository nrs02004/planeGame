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
#include <stack>
#include "layer.h"

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

    std::vector<Action*> actions;

    std::string filename="level/level1.lua";
    Level* Level1 = new Level(filename, L, images, myShip);
    
    Layer* current_layer;
    
    std::stack<Layer*> layers; // Creating the layer stack
    layers.push(Level1); // Adding the level layer!
    
    srand(time(0));

    current_time = SDL_GetTicks();
    //While the user hasn't quit
      while( quit == false )
	{
    //Finding how much time has passed
	  dt = update_time(old_time, current_time);

	  //Checking for key presses
	  handle_event(event, quit, actions);
	  
        (layers.top())->update(dt,actions,layers);
        (layers.top())->display();
        
        //Removing Layers that have ended
        while(layers.top()->terminate == true){
            layers.pop();
        }

	}
          
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
