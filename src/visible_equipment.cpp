//
//  visible_equipment.cpp
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "visible_equipment.h"
#include "defs.h"
#include <math.h>
#include <iostream>

Visible_equipment::Visible_equipment(float* _x_ptr, float* _y_ptr, Image* _my_image, Color _color){
    x_ptr = _x_ptr; y_ptr = _y_ptr;
    my_image = _my_image;
    color = _color;
    angle = 0.0;
}


//////// SHIELD

Shield::Shield(float* _x_ptr, float* _y_ptr, Image* _my_image, Color _color) : Visible_equipment(_x_ptr, _y_ptr, _my_image, _color)
{
    length = 0.5;
    remaining = 0.0;
    active = false;
    max_color = _color;
}
void Shield::activate()
{
    remaining = length;
    active = true;
    color = max_color; //reseting the color to the initial color
}

void Shield::update(float dt)
{
    if(remaining > 0.0){
        remaining -= dt;
        color.r = fmax((int)((float)max_color.r *(1 - (1-remaining/length))),10);
        color.g = fmax((int)((float)max_color.g *(1 - 1*pow(1-remaining/length, 2))),10);
        color.b = fmax((int)((float)max_color.b *(1 - 1.2*(1-remaining/length))),10);
    }
    else{
        active = false;
    }
}