//
//  event.cpp
//  airplaneGame
//
//  Created by noah simon on 10/11/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "event.h"

void handle_event(SDL_Event &event, bool &quit, std::vector<Action*> &actions)
{
    //While there's events to handle
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            //Quit the program
            quit = true;
        }
        
        if( event.type == SDL_MOUSEBUTTONDOWN )
        {
            int x,y;
            SDL_GetMouseState( &x, &y );
            mouse_click *myAction = new mouse_click(x,y);
            actions.push_back(myAction);
        }
    }
    
    // //Get the keystates
     const Uint8 *keystates = SDL_GetKeyboardState( NULL );
    
    //If up is pressed
     if( keystates[ SDL_SCANCODE_UP ] )
       {
	 y_thruster *myAction = new y_thruster(-1.0);
	 actions.push_back(myAction);
       }
    
     //If down is pressed
     if( keystates[ SDL_SCANCODE_DOWN ] )
      {
        y_thruster *myAction = new y_thruster(1.0);
        actions.push_back(myAction);
      }
     
    //If left is pressed
     if( keystates[ SDL_SCANCODE_LEFT ] )
       {
	 x_thruster *myAction = new x_thruster(-1.0);
	 actions.push_back(myAction);
    }
     
     //If right is pressed
     if( keystates[ SDL_SCANCODE_RIGHT ] )
       {
	 x_thruster *myAction = new x_thruster(1.0);
	 actions.push_back(myAction);
       }
    
     
     if( keystates[ SDL_SCANCODE_SPACE ] )
       {
        fire_weapon *myAction = new fire_weapon();
        actions.push_back(myAction);
       }     
}
