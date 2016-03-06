//
//  action.cpp
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "action.h"

Action::Action(){}

x_thruster::x_thruster(float init_direction)
{
    direction = init_direction;
    action_type = THRUST;
}

y_thruster::y_thruster(float init_direction)
{
    direction = init_direction;
    action_type = THRUST;
}

fire_weapon::fire_weapon()
{
    action_type = FIRE;
}

mouse_click::mouse_click(int _x, int _y)
{
    x = _x;
    y = _y;
    action_type = CLICK;
}

void x_thruster::apply(Ship *myShip, float dt)
{
    myShip->x_thrust(dt * direction * myShip->accel);
}

void y_thruster::apply(Ship *myShip, float dt)
{
    myShip->y_thrust(dt * direction * myShip->accel);
}

void fire_weapon::apply(Ship *myShip, float dt, std::vector<Bullet*>& bullets)
{
    myShip->fire(bullets);
    std::cout << "FIRING 0 \n";
}

// THIS NEEDS TO BE UPDATED WHEN WE HAVE BUTTONS!

void mouse_click::apply()
{
    std::cout << x << " " << y << " \n";
}

// Initial definitions for our virtual functions

void Action::apply(){}
void Action::apply(Ship *myShip, float dt){}
void Action::apply(Ship *myShip, float dt, std::vector<Bullet*>& bullets){}
