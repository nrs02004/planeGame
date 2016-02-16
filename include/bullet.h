//
//  bullet.h
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__bullet__
#define __airplaneGame__bullet__

#include <iostream>
#include "SDL/SDL.h"
#include "defs.h"
#include "image.h"
#include "physicalObject.h"

class Bullet : public PhysicalObject{
public:
  Bullet(float init_x, float init_y, float init_vel_x, float init_vel_y, float init_accel_y, Image* init_bullet_image);
  ~Bullet();
    void update(float dt);
    bool within_bounds(float max_y, float max_x);
    void explode();
    
    float x_vel,y_vel,max_vel;
    float y_accel;
    bool exploded;
    float damage;
};


#endif /* defined(__airplaneGame__bullet__) */
