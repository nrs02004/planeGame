#ifndef LUA_OBJ_H
#define LUA_OBJ_H

#include <math.h>
#include <string>
#include "hitbox.h"

class Ship_dat {
public:
    float speed;
    float life;
    float cool_down_length;
    std::string name;
    float x;
    float y;
    std::string color;
    std::string weapon_name;
    std::vector<Hitbox> hitboxes;

 Ship_dat(float _speed, float _life, float _cool_down_length, std::string _name, float _x, float _y, std::string _color, std::string _weapon_name, std::vector<Hitbox> _hitboxes) : speed(_speed), life(_life), cool_down_length(_cool_down_length), name(_name), x(_x), y(_y), color(_color), weapon_name(_weapon_name), hitboxes(_hitboxes) {}
};

class Weapon_dat {
 public:
  int alternate;
  float portWidth, cool_down_length, bullet_accel_x, bullet_accel_y, bullet_init_speed_x, bullet_init_speed_y, bullet_dmg;
  std::string bullet_name, gun_name, bullet_color;
  std::vector<Hitbox> hitboxes;

 Weapon_dat(int _alternate, float _portWidth, float _cool_down_length, float _bullet_accel_x, float _bullet_accel_y, float _bullet_init_speed_x, float _bullet_init_speed_y, float _bullet_dmg, std::string _bullet_name, std::string _gun_name, std::string _bullet_color, std::vector<Hitbox> _hitboxes) : alternate(_alternate), portWidth(_portWidth), cool_down_length(_cool_down_length), bullet_accel_x(_bullet_accel_x), bullet_accel_y(_bullet_accel_y), bullet_init_speed_x(_bullet_init_speed_x), bullet_init_speed_y(_bullet_init_speed_y), bullet_dmg(_bullet_dmg), bullet_name(_bullet_name), gun_name(_gun_name), bullet_color(_bullet_color), hitboxes(_hitboxes) {}
};

class Image_dat{
 public:
  std::string name, path;
  float width, height;
  int alpha;

 Image_dat(std::string _name, std::string _path, float _width, float _height, int _alpha) : name(_name), path(_path), width(_width), height(_height), alpha(_alpha){}
};

class Color_dat{
 public:
  std::string name;
  int r,g,b;

 Color_dat(std::string _name, int _r, int _g, int _b) : name(_name), r(_r), g(_g), b(_b){}
};

class myShip_dat{
 public:
  std::vector<std::string> weapon_names;
  float accel, max_vel, life;
  std::string color_name;
  std::vector<Hitbox> hitboxes;
};

#endif
