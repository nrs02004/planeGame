#ifndef __airplaneGame__layer__
#define __airplaneGame__layer__

#include <iostream>
#include "action.h"
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "image.h"
#include "lua/lua.hpp"
#include "SDL2/SDL.h"
#include "color.h"
#include "ship.h"
#include "lua_binding.h"
#include "globals.h"

class Layer
{
public:
  Layer();
    virtual void update(float, std::vector<Action*> &, std::stack<Layer*> &);
    virtual void display();

    bool terminate;
};

class pause_layer : public Layer
{
public:
    pause_layer();
    void update(float, std::vector<Action*> &, std::stack<Layer*> &);
    void display();
    void apply_actions(std::vector<Action*> &, std::stack<Layer*> &);
};

class Intro : public Layer
{
public:
  Intro(lua_State*, Ship *);
    void update(float, std::vector<Action*> &, std::stack<Layer*> &);
    void display();
    void apply_actions(std::vector<Action*> &, std::stack<Layer*> &);
    Ship* init_ship(lua_State*);

    bool start_level;
    lua_State *L;
    Ship *myShip;
    int count;
};

#endif /* defined(__airplaneGame__layer__) */
