//
//  ship.h
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__ship__
#define __airplaneGame__ship__

#include "bullet.h"
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include "image.h"
#include "physicalObject.h"

class Ship : public PhysicalObject{
public:
  Ship(float, float, std::vector<Image*> *) ;
  ~Ship();
    
    void update(float dt);
    void x_thrust(float power);
    void y_thrust(float power);
    void passive_break_x(float power);
    void passive_break_y(float power);
    void fire(std::vector<Bullet*>& bullets, Image* bullet_image);
    void enforce_bounds(float, float);
    
    float x_vel,y_vel,max_vel,accel,cool_down_timer, cool_down_length;
    bool active_thrust_x, active_thrust_y;
    int banking;
    int firePort;
};

#endif /* defined(__airplaneGame__ship__) */