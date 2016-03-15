#include "lua/lua.hpp"
#include "luaObj.h"
#include<iostream>
#include<vector>
#include "lua_binding.h"

void load_file(lua_State *L, std::string& filename){
  if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
    luaL_error(L, "cannot run configuration file: %s",
	  lua_tostring(L, -1)); //Error handling
}

int lua_get_int(lua_State *L, const std::string& key){
  lua_getglobal(L, key.c_str());
      if(!lua_isnumber(L, -1)) {
	luaL_error(L, "Not a number: %s", key.c_str());
      }
      int outp = (int)lua_tonumber(L,-1);
      lua_pop(L,1);
      return outp;
}

float lua_get_float(lua_State *L, const std::string& key){
  lua_getglobal(L, key.c_str());
      if(!lua_isnumber(L, -1)) {
	luaL_error(L, "Not a number: %s", key.c_str());
      }
      float outp = (float)lua_tonumber(L,-1);
      lua_pop(L,1);
      return outp;
}

bool lua_get_bool(lua_State *L, const std::string& key){
  lua_getglobal(L, key.c_str());
      if(!lua_isboolean(L, -1)) {
	luaL_error(L, "Not a bool: %s", key.c_str());
      }
      bool outp = (bool)lua_toboolean(L,-1);
      lua_pop(L,1);
      return outp;
}

std::string lua_get_string(lua_State *L, const std::string& key){
  lua_getglobal(L, key.c_str());
      if(!lua_isstring(L, -1)) {
	luaL_error(L, "Not a string: %s", key.c_str());
      }
      std::string outp = std::string(lua_tostring(L,-1));
      lua_pop(L,1);
      return outp;
}

std::vector<int> lua_get_int_vec(lua_State *L, const std::string& key){
  lua_getglobal(L, key.c_str());
  std::vector<int> outp;
  if(!lua_istable(L, -1)) {
    luaL_error(L, "Not a table: %s", key.c_str());
  }
  lua_pushnil(L);
  while(lua_next(L, -2)) {
    outp.push_back((int)lua_tonumber(L, -1));
    lua_pop(L, 1);
  }
  lua_pop(L, 2);
  return outp;
}

std::vector<std::string> lua_get_string_vec(lua_State *L, const std::string& key){
  lua_pushstring(L,key.c_str());
  lua_gettable(L,-2);
  std::vector<std::string> outp;
  if(!lua_istable(L, -1)) {
    luaL_error(L, "Not a table: %s", key.c_str());
  }
  lua_pushnil(L);
  while(lua_next(L, -2)) {
    outp.push_back(lua_tostring(L, -1));
    lua_pop(L, 1);
    }
  lua_pop(L, 1);
  return outp;
}

//Gets a string from table on top of stack
std::string lua_get_string_from_table(lua_State *L, const std::string& key){
    lua_pushstring(L,key.c_str());
    lua_gettable(L,-2);
    std::string outp = std::string(lua_tostring(L,-1));
    lua_pop(L,1);
    return outp;
}

//Gets an int from table on top of stack
int lua_get_int_from_table(lua_State *L, const std::string& key){
    lua_pushstring(L,key.c_str());
    lua_gettable(L,-2);
    int outp = (int)lua_tonumber(L,-1);
    lua_pop(L,1);
    return outp;
}

//Gets a float from table on top of stack
float lua_get_float_from_table(lua_State *L, const std::string& key){
  lua_pushstring(L,key.c_str());
  lua_gettable(L,-2);
  float outp = (float)lua_tonumber(L,-1);
  lua_pop(L,1);
  return outp;
}

//Gets a vector of ship data
std::vector<Ship_dat*> lua_get_ships(lua_State *L, const std::string& key){
    lua_getglobal(L, key.c_str());
    std::vector<Ship_dat*> outp;
    if(!lua_istable(L, -1)) {
        luaL_error(L, "Not a table: %s", key.c_str());
    }
    lua_pushnil(L);

    int x,y,speed,life;
    float cool_down_length;
    std::string name, color;

    while(lua_next(L, -2)) {
        x = lua_get_float_from_table(L, "x");
        y = lua_get_float_from_table(L, "y");
        speed = lua_get_float_from_table(L, "speed");
        life = lua_get_float_from_table(L, "life");
        cool_down_length = lua_get_float_from_table(L, "cool_down_length");
        name = lua_get_string_from_table(L, "name");
	color = lua_get_string_from_table(L, "color");

	std::string hitbox_string = "hitboxes";
	std::vector<Hitbox> hitboxes = lua_get_hitboxes_from_table(L,hitbox_string);

        Ship_dat* ship_dat = new Ship_dat(speed,life,cool_down_length,name,x,y,color, hitboxes);
        outp.push_back(ship_dat);
        lua_pop(L, 1);
    }
    lua_pop(L, 2);
    return outp;
}


//Gets weapon types
std::vector<Weapon_dat*> lua_get_weapons(lua_State *L, const std::string& key){
    lua_getglobal(L, key.c_str());
    std::vector<Weapon_dat*> outp;
    if(!lua_istable(L, -1)) {
        luaL_error(L, "Not a table: %s", key.c_str());
    }
    lua_pushnil(L);

    int alternate;
    float portWidth, cool_down_length, bullet_accel_x, bullet_accel_y, bullet_init_speed_x, bullet_init_speed_y, bullet_dmg;
    std::string bullet_name, gun_name, bullet_color;


    while(lua_next(L, -2)) {
      alternate = lua_get_int_from_table(L,"alternate");
      portWidth = lua_get_float_from_table(L,"portWidth");
      cool_down_length = lua_get_float_from_table(L, "cool_down_length");
      bullet_accel_x = lua_get_float_from_table(L, "bullet_accel_x");
      bullet_accel_y = lua_get_float_from_table(L, "bullet_accel_y");
      bullet_init_speed_x = lua_get_float_from_table(L, "bullet_init_speed_x");
      bullet_init_speed_y = lua_get_float_from_table(L, "bullet_init_speed_y");
      bullet_dmg = lua_get_float_from_table(L, "bullet_dmg");
      bullet_name = lua_get_string_from_table(L, "bullet_name");
      gun_name = lua_get_string_from_table(L, "gun_name");
      bullet_color = lua_get_string_from_table(L, "bullet_color");

      std::string hitbox_string = "hitboxes";
      std::vector<Hitbox> hitboxes = lua_get_hitboxes_from_table(L,hitbox_string);

      Weapon_dat* weapon_dat = new Weapon_dat(alternate, portWidth, cool_down_length, bullet_accel_x, bullet_accel_y,
					      bullet_init_speed_x, bullet_init_speed_y, bullet_dmg, bullet_name, gun_name,
					      bullet_color, hitboxes);

      outp.push_back(weapon_dat);
      lua_pop(L, 1);
      }
    lua_pop(L, 2);
    return outp;
}



//Gets images
std::vector<Image_dat*> lua_get_images(lua_State *L, const std::string& key){
    lua_getglobal(L, key.c_str());
    std::vector<Image_dat*> outp;
    if(!lua_istable(L, -1)) {
        luaL_error(L, "Not a table: %s", key.c_str());
    }
    lua_pushnil(L);

    std::string name, path;
    float width, height;
    int alpha;

    while(lua_next(L, -2)) {
      name = lua_get_string_from_table(L, "name");
      path = lua_get_string_from_table(L, "path");
      width = lua_get_float_from_table(L, "width");
      height = lua_get_float_from_table(L, "height");
      alpha = lua_get_int_from_table(L, "alpha");

      Image_dat* image_dat = new Image_dat(name, path, width, height, alpha);

      outp.push_back(image_dat);
      lua_pop(L, 1);
      }
      lua_pop(L, 1);
    return outp;
}


// Get colors
std::vector<Color_dat*> lua_get_colors(lua_State *L, const std::string& key){
    lua_getglobal(L, key.c_str());
    std::vector<Color_dat*> outp;
    if(!lua_istable(L, -1)) {
        luaL_error(L, "Not a table: %s", key.c_str());
    }
    lua_pushnil(L);

    std::string name;
    int r,g,b;

    while(lua_next(L, -2)) {
      name = lua_get_string_from_table(L, "name");
      r = lua_get_int_from_table(L, "r");
      g = lua_get_int_from_table(L, "g");
      b = lua_get_int_from_table(L, "b");

      Color_dat* color_dat = new Color_dat(name, r, g, b);

      outp.push_back(color_dat);
      lua_pop(L, 1);
      }
    lua_pop(L, 1);
    return outp;
}


//Gets a vector of hitboxes
std::vector<Hitbox> lua_get_hitboxes_from_table(lua_State *L, const std::string& key){
  lua_pushstring(L,key.c_str());
  lua_gettable(L,-2);
  std::vector<Hitbox> outp;
   if(!lua_istable(L, -1)) {
        luaL_error(L, "Not a table: %s", key.c_str());
    }
    lua_pushnil(L);
    int x,y,r;
    
     while(lua_next(L, -2)) {
      x = lua_get_float_from_table(L, "x");
      y = lua_get_float_from_table(L, "y");
      r = lua_get_float_from_table(L, "r");
      outp.push_back(Hitbox(x,y,r));
      lua_pop(L, 1);
     }
  lua_pop(L, 1);
    return outp;
}


myShip_dat lua_get_myShip(lua_State *L, const std::string& key){
  lua_getglobal(L, key.c_str());
  myShip_dat outp;
  if(!lua_istable(L, -1)) {
    luaL_error(L, "Not a table: %s", key.c_str());
  }
    
  outp.accel = lua_get_float_from_table(L, "accel");
   outp.max_vel = lua_get_float_from_table(L, "max_vel");
   outp.life = lua_get_float_from_table(L, "life");
   outp.color_name = lua_get_string_from_table(L, "color");
   outp.weapon_names = lua_get_string_vec(L, "weapons");

   std::string hitbox_string = "hitboxes";
   outp.hitboxes = lua_get_hitboxes_from_table(L,hitbox_string);
   
   lua_pop(L, 1);
   
   return outp;
}
