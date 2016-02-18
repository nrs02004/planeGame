//
//  action.h
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__action__
#define __airplaneGame__action__

#include <iostream>
#include "ship.h"
#include "bullet.h"
#include <vector>
#include <string>
#include "image.h"

enum action_types{THRUST, FIRE, CLICK};

class Action
{
public:
    Action();
    virtual void apply();
    virtual void apply(Ship *myShip, float dt);
    virtual void apply(Ship *myShip, float dt, std::vector<Bullet*>& bullets, Image* bullet_image);
    
    action_types action_type;
};

class x_thruster : public Action
{
public:
    x_thruster(float init_direction);
    void apply(Ship *myShip, float dt);
    float direction;
};

class y_thruster : public Action
{
public:
    y_thruster(float init_direction);
    void apply(Ship *myShip, float dt);
    float direction;
};

class fire_weapon : public Action
{
public:
    fire_weapon();
    void apply(Ship *myShip, float dt, std::vector<Bullet*>& bullets, Image* bullet_image);
};

class mouse_click : public Action{
public:
    mouse_click(int, int);
    void apply();
    float x,y;
};
#endif /* defined(__airplaneGame__action__) */
