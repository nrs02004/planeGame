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

#endif