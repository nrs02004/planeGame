#ifndef LUA_OBJ_H
#define LUA_OBJ_H

#include <math.h>
#include <string>

class Ship_dat {
public:
    float speed;
    float life;
    float cool_down_length;
    std::string image_file;
    float x;
    float y;

    Ship_dat(float _speed, float _life, float _cool_down_length, std::string _image_file, float _x, float _y) : speed(_speed), life(_life), cool_down_length(_cool_down_length), image_file(_image_file), x(_x), y(_y) {}
};

class Weapon_dat {
 public:
  int alternate;
  float portWidth, cool_down_length, bullet_accel_x, bullet_accel_y, bullet_init_speed_x, bullet_init_speed_y, bullet_dmg;
  std::string bullet_name, gun_name;

  Weapon_dat(int _alternate, float _portWidth, float _cool_down_length, float _bullet_accel_x, float _bullet_accel_y, float _bullet_init_speed_x, float _bullet_init_speed_y, float _bullet_dmg, std::string _bullet_name, std::string _gun_name) : alternate(_alternate), portWidth(_portWidth), cool_down_length(_cool_down_length), bullet_accel_x(_bullet_accel_x), bullet_accel_y(_bullet_accel_y), bullet_init_speed_x(_bullet_init_speed_x), bullet_init_speed_y(_bullet_init_speed_y), bullet_dmg(_bullet_dmg), bullet_name(_bullet_name), gun_name(_gun_name) {}
};

class Image_dat{
 public:
  std::string name, path;
  float width, height;

    Image_dat(std::string _name, std::string _path, float _width, float _height) : name(_name), path(_path), width(_width), height(_height){}
};

#endif
