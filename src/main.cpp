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
#include "weapon.h"

SDL_Window* gWindow = NULL;
std::map<std::string, Color*> colors;
std::map<std::string, Weapon*> weapon_list;
std::map<std::string, Image*> images;

int main( int argc, char* args[] )
{

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  SDL_Renderer* renderer = NULL;

  init(renderer);

  //Reading in images from Lua
  init_images(L, renderer);

  // Reading in colors from Lua
  init_colors(L);
    
  // loading weapons from Lua
  
  init_weapons(L);

  // load ship from Lua and init
  
  Ship *myShip = init_ship(L);
    
  std::vector<Action*> actions; // Creating action vector (should be stack)

  std::stack<Layer*> layers; // Creating the layer stack

  Intro* intro = new Intro(L, myShip, renderer);

  layers.push(intro); //Adding the intro layer

  srand(time(0));

  SDL_Event event;
  Uint32 old_time, current_time;
  float dt;
  bool quit = false;
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
  
  clean_up();
  delete myShip;
  
  return 0;
}


void init_images(lua_State *L, SDL_Renderer* renderer)
{
  std::string init_filename = "init/init.lua";
  load_file(L, init_filename);
  std::string image_data = "images";
  std::vector<Image_dat*> image_dat = lua_get_images(L, image_data);

  //Loading all the images
  for(auto imageIt = image_dat.begin(); imageIt != image_dat.end(); imageIt++){
    images[(*imageIt)->name] = new Image(NULL, (*imageIt)->width, (*imageIt)->height);
    (images[(*imageIt)->name])->image = load_texture((*imageIt)->path, renderer);
    SDL_SetTextureBlendMode( (images[(*imageIt)->name])->image, SDL_BLENDMODE_BLEND ); // setting blending
    SDL_SetTextureAlphaMod( (images[(*imageIt)->name])->image, (*imageIt)->alpha );
  }
}

void init_colors(lua_State *L)
{
  std::string colors_filename = "init/colors.lua";
  load_file(L, colors_filename);
  std::string color_data = "colors";
  std::vector<Color_dat*> color_dat = lua_get_colors(L, color_data);
  
  for(auto colorIt = color_dat.begin(); colorIt != color_dat.end(); colorIt++){
    colors[(*colorIt)->name] = new Color((*colorIt)->r, (*colorIt)->g, (*colorIt)->b);
  }
}

void init_weapons(lua_State *L)
{
  std::string weapon_filename = "objects/weapon_list.lua";
  load_file(L, weapon_filename);
  std::string weapon_data = "weapon_list";
  std::vector<Weapon_dat*> weapon_dat = lua_get_weapons(L, weapon_data);
  
  //Weapon list is global
  
  for(auto wIt = weapon_dat.begin(); wIt != weapon_dat.end(); wIt++){
    Weapon *newWeapon = new Weapon((*wIt)->alternate, (*wIt)->portWidth,
				   (*wIt)->cool_down_length, (*wIt)->bullet_accel_x,
				   (*wIt)->bullet_accel_y, (*wIt)->bullet_init_speed_x,
				   (*wIt)->bullet_init_speed_y, (*wIt)->bullet_dmg,
				   images[(*wIt)->bullet_name],
				   *colors[(*wIt)->bullet_color],
				   (*wIt)->hitboxes);
    
    weapon_list[(*wIt)->gun_name] = newWeapon;
  }
}


Ship* init_ship(lua_State *L)
{
  std::string myShip_filename = "objects/myShip.lua";
  load_file(L, myShip_filename);
  myShip_dat myShip_data = lua_get_myShip(L,"ship");
   
  std::vector<Image*> *ship_images = new std::vector<Image*>;
  ship_images->push_back(images["ship_image"]);
  ship_images->push_back(images["ship_imageL"]);
  ship_images->push_back(images["ship_imageR"]);
  ship_images->push_back(images["ship_imageLL"]);
  ship_images->push_back(images["ship_imageRR"]);
  
  Ship *myShip = new Ship(240, 190, ship_images, *colors[myShip_data.color_name], myShip_data.accel, myShip_data.max_vel, myShip_data.life, myShip_data.hitboxes);
  
  // Adding Weapons to Ship
  
  for(auto it = (myShip_data.weapon_names).begin(); it != (myShip_data.weapon_names).end(); it++){
    myShip->add_weapon(weapon_list[*it]);
  }
  
  return myShip;
}


void clean_up()
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
