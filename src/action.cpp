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

void x_thruster::apply(Ship *myShip, float dt)
{
    myShip->x_thrust(dt * direction * myShip->accel);
}

void y_thruster::apply(Ship *myShip, float dt)
{
    myShip->y_thrust(dt * direction * myShip->accel);
}

void fire_weapon::apply(Ship *myShip, float dt, std::vector<Bullet*>& bullets, Image* bullet_image)
{
    myShip->fire(bullets, bullet_image);
}

// Initial definitions for our virtual functions

void Action::apply(Ship *myShip, float dt){}
void Action::apply(Ship *myShip, float dt, std::vector<Bullet*>& bullets, Image* bullet_image){}
