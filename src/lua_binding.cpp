#include "lua/lua.hpp"
#include "luaObj.h"
#include<iostream>
#include<vector>

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
    std::string image_file;
    
    while(lua_next(L, -2)) {
        x = lua_get_float_from_table(L, "x");
        y = lua_get_float_from_table(L, "y");
        speed = lua_get_float_from_table(L, "speed");
        life = lua_get_float_from_table(L, "life");
        cool_down_length = lua_get_float_from_table(L, "cool_down_length");
        image_file = lua_get_string_from_table(L, "image_file");
        
        Ship_dat* ship_dat = new Ship_dat(speed,life,cool_down_length,image_file,x,y);
        outp.push_back(ship_dat);
        lua_pop(L, 1);
    }
    lua_pop(L, 2);
    return outp;
}
