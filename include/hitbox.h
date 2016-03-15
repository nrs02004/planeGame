#ifndef __airplaneGame__hitbox__
#define __airplaneGame__hitbox__

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "lua/lua.hpp"
#include "SDL2/SDL.h"
#include "color.h"

class Hitbox
{
public:
 Hitbox(float _x, float _y, float _r ) : x(_x),
    y(_y), r(_r) {}
  float x, y, r;
};

#endif
