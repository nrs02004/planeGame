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

int main( int argc, char* args[] )
{

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  std::map<std::string, Image*> images;

  SDL_Renderer* renderer = NULL;

  init(renderer);

  //Reading in images from Lua
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
  
  // Reading in colors from Lua
  std::string colors_filename = "init/colors.lua";
  load_file(L, colors_filename);
  std::string color_data = "colors";
  std::vector<Color_dat*> color_dat = lua_get_colors(L, color_data);
  
  //Load colors
  for(auto colorIt = color_dat.begin(); colorIt != color_dat.end(); colorIt++){
    colors[(*colorIt)->name] = new Color((*colorIt)->r, (*colorIt)->g, (*colorIt)->b);
  }
  

  SDL_Event event;

  Uint32 old_time, current_time;
  float dt;
  current_time = SDL_GetTicks();

  //Quit flag
  bool quit = false;

  std::string myShip_filename = "objects/myShip.lua";
  load_file(L, myShip_filename);
  myShip_dat myShip_data = lua_get_myShip(L,"ship");

  std::vector<Image*> ship_images;
  ship_images.push_back(images["ship_image"]);
  ship_images.push_back(images["ship_imageL"]);
  ship_images.push_back(images["ship_imageR"]);
  ship_images.push_back(images["ship_imageLL"]);
  ship_images.push_back(images["ship_imageRR"]);

  Ship *myShip = new Ship(240, 190, &ship_images, *colors[myShip_data.color_name], myShip_data.accel, myShip_data.max_vel, myShip_data.life, myShip_data.hitboxes);

    // loading weapons
    std::string weapon_filename = "objects/weapon_list.lua";
    load_file(L, weapon_filename);
    std::string weapon_data = "weapon_list";
    std::vector<Weapon_dat*> weapon_dat = lua_get_weapons(L, weapon_data);

    std::map<std::string, Weapon*> weapon_list;

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

    myShip->add_weapon(weapon_list["purple_machine_gun"]);
    myShip->add_weapon(weapon_list["green_missile_launcher"]);
    myShip->add_weapon(weapon_list["blue_minigun_L"]);
    myShip->add_weapon(weapon_list["blue_minigun_R"]);
    
    std::vector<Action*> actions;

    std::stack<Layer*> layers; // Creating the layer stack

    Intro* intro = new Intro(L, images, myShip, renderer);

    layers.push(intro); //Adding the intro layer

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
    delete myShip;
  
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
