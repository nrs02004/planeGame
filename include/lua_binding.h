#ifndef LUA_BINDING_H
#define LUA_BINDING_H

#include "luaObj.h"
#include "lua/lua.hpp"
#include<string>
#include "color.h"

void load_file(lua_State *, std::string&);

int lua_get_int(lua_State *, const std::string&);

float lua_get_float(lua_State *, const std::string& key);

bool lua_get_bool(lua_State *, const std::string&);

std::string lua_get_string(lua_State *, const std::string&);

std::vector<int> lua_get_int_vec(lua_State *, const std::string&);

std::vector<std::string> lua_get_string_vec(lua_State *, const std::string&);

std::vector<std::string> lua_get_string_vec_from_table(lua_State *, const std::string&);

std::string lua_get_string_from_table(lua_State *, const std::string&);

int lua_get_int_from_table(lua_State *, const std::string&);

float lua_get_float_from_table(lua_State *, const std::string&);

std::vector<Hitbox> lua_get_hitboxes_from_table(lua_State *, const std::string&);

std::vector<Ship_dat*> lua_get_ships(lua_State *, const std::string&);

std::vector<Weapon_dat*> lua_get_weapons(lua_State *, const std::string&);

std::vector<Image_dat*> lua_get_images(lua_State *, const std::string&);

std::vector<Color_dat*> lua_get_colors(lua_State *, const std::string&);

myShip_dat lua_get_myShip(lua_State *, const std::string&);
#endif
