//
//  event.h
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#ifndef __airplaneGame__event__
#define __airplaneGame__event__

#include <iostream>
#include "SDL2/SDL.h"
//#include "SDL/SDL_image.h"
#include "ship.h"
#include "bullet.h"
#include "vector"
#include "action.h"

void handle_event(SDL_Event&, bool&, std::vector<Action*> &actions);

#endif /* defined(__airplaneGame__event__) */
