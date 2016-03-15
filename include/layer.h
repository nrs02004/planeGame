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
#include "image.h"
#include "SDL2/SDL.h"
#include "color.h"

class Layer
{
public:
  Layer(SDL_Renderer* );
    virtual void update(float, std::vector<Action*> &, std::stack<Layer*> &);
    virtual void display();

    bool terminate;
    SDL_Renderer* renderer;
};

class pause : public Layer
{
public:
    pause(SDL_Renderer*);
    void update(float, std::vector<Action*> &, std::stack<Layer*> &);
    void display();
    void apply_actions(std::vector<Action*> &, std::stack<Layer*> &);
};

class Intro : public Layer
{
public:
  Intro(lua_State*, std::map<std::string, Image*>, Ship *, SDL_Renderer*);
    void update(float, std::vector<Action*> &, std::stack<Layer*> &);
    void display();
    void apply_actions(std::vector<Action*> &, std::stack<Layer*> &);

    bool start_level;
    lua_State *L;
    std::map<std::string, Image*> images;
    Ship *myShip;
    int count;
};

#endif /* defined(__airplaneGame__layer__) */
