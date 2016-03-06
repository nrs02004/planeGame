//
//  ship.h
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__weapon__
#define __airplaneGame__weapon__

#include "bullet.h"
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include "image.h"

class Weapon{
public:
  Weapon(int, float, float,
	 float, float, float, float, float, Image*) ;
  ~Weapon();
    
    void update(float dt);
    void fire(std::vector<Bullet*>&, float, float);
    
    float cool_down_timer, cool_down_length, portWidth;
    int firePort, alternate;

    //Bullet attributes
    float bullet_accel_x, bullet_accel_y, bullet_init_speed_x, bullet_init_speed_y, bullet_dmg;
    Image* bullet_image;
};

#endif /* defined(__airplaneGame__ship__) */
