//
//  display.cpp
//  airplaneGame
//
//  Created by noah simon on 10/10/13.
//  Copyright (c) 2013 DinaAndTheNoahs. All rights reserved.
//

#include "display.h"
#include "defs.h"
#include "ship.h"
#include <string>
#include <iostream>
#include "globals.h"

SDL_Surface *load_image( std::string filename , SDL_Surface* screen)
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
      {
	//Create an optimized image
	optimizedImage = SDL_ConvertSurface( loadedImage, screen->format, 0 );
	
	//Free the old image
	SDL_FreeSurface( loadedImage );
        
	if( optimizedImage != NULL )
	  {
	    //Map the color key
	    Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
            
	    //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
	    SDL_SetColorKey( optimizedImage, SDL_TRUE, colorkey );
	  }
        
      }
    
    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}


bool init(SDL_Surface* &screen)
{
    
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }
    
    //Set up the screen
    gWindow = SDL_CreateWindow( "Plane Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    screen = SDL_GetWindowSurface( gWindow );
    //screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return 1;
    }
    
    //If everything initialized fine
    return true;
}

void apply_PhysicalObject(SDL_Surface *screen, PhysicalObject *obj, int index = 0)
{
  apply_surface(obj->x - (*(obj->my_images))[index]->width/2, obj->y - (*(obj->my_images))[index]->height/2, (*(obj->my_images))[index]->image, screen);
}

void apply_enemyShip(SDL_Surface *screen, EnemyShip *ship)
{
  //  (ship->exhaust_flames)->display();
  apply_PhysicalObject(screen, ship);
}

void apply_Bullet(SDL_Surface *screen, Bullet *bullet)
{
  //  (bullet->exhaust_flames)->display();
  apply_PhysicalObject(screen, (PhysicalObject *)bullet);
}

void apply_Ship(SDL_Surface *screen, Ship *ship)
{
  //  (ship->exhaust_flames)->display();
  if(ship->banking == 0) apply_PhysicalObject(screen, (PhysicalObject *)ship);
  if(ship->banking == -1) apply_PhysicalObject(screen, (PhysicalObject *)ship, 1);
  if(ship->banking == -2) apply_PhysicalObject(screen, (PhysicalObject *)ship, 3);
  if(ship->banking == 1) apply_PhysicalObject(screen, (PhysicalObject *)ship, 2);
  if(ship->banking == 2) apply_PhysicalObject(screen, (PhysicalObject *)ship, 4);

}



bool update_disp(SDL_Surface* screen, SDL_Surface* background, Ship* myShip, std::vector<Bullet*> &bullets, std::vector<EnemyShip*> &enemies, std::vector<Bullet*> &enemy_bullets)
{
    //Apply the background to screen
    apply_surface( 0, 0, background, screen );
    
    //Apply bullets to screen
    if(!bullets.empty())
    {
        for(std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++){
	  //            apply_surface(it->x, it->y, it->bullet_image, screen);
	  apply_Bullet(screen, *it);
        }
    }

    //Apply Ship to screen
    apply_Ship(screen, myShip);

    //Apply enemie bullets to screen
    if(!enemy_bullets.empty())
    {
        for(std::vector<Bullet*>::iterator it = enemy_bullets.begin(); it != enemy_bullets.end(); it++){
	  //           apply_surface(it->x, it->y, it->bullet_image, screen);
	  apply_PhysicalObject(screen, *it);
        }
    }


    //Apply enemies to screen
    if(!enemies.empty())
    {
        for(std::vector<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end(); it++){
	  //            apply_surface(it->x, it->y, it->enemy_image, screen);
	  apply_enemyShip(screen, *it);
        }
    }
    
    //Update the screen
    SDL_UpdateWindowSurface(gWindow);
    return 1;
}
