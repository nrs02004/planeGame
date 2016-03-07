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

SDL_Texture* load_texture( std::string filename , SDL_Renderer* renderer )
{
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedImage = IMG_Load( filename.c_str() );

  //Map the color key
  Uint32 colorkey = SDL_MapRGB( loadedImage->format, 0, 0xFF, 0xFF );

  //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
  SDL_SetColorKey( loadedImage, SDL_TRUE, colorkey );

    //If nothing went wrong in loading the image
  if( loadedImage != NULL )
    {
      //Create a texture
      newTexture = SDL_CreateTextureFromSurface(renderer, loadedImage);
      //Free the old image
      SDL_FreeSurface( loadedImage );
      }
  return newTexture;
}

void apply_texture( int x, int y, int width, int height, SDL_Texture* source, SDL_Renderer* renderer, double angle)
{
    //Make a temporary rectangle to hold the offsets
  SDL_Rect renderQuad = {x, y, width, height};
  //add the texture
  SDL_RenderCopyEx( renderer, source, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
}


bool init(SDL_Renderer* &renderer)
{

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }

    //Set up the screen
    gWindow = SDL_CreateWindow( "Plane Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    int imgFlags = IMG_INIT_PNG;

    IMG_Init( imgFlags );

    return true;
}

void apply_PhysicalObject(SDL_Renderer *renderer, PhysicalObject *obj, int index = 0)
{
  apply_texture(obj->x - (*(obj->my_images))[index]->width/2, obj->y - (*(obj->my_images))[index]->height/2,  (*(obj->my_images))[index]->width,  (*(obj->my_images))[index]->height, (*(obj->my_images))[index]->image, renderer, (*(obj->my_images))[index]->angle);
}

void apply_enemyShip(SDL_Renderer *renderer, EnemyShip *ship)
{
  apply_PhysicalObject(renderer, ship);
}

void apply_Bullet(SDL_Renderer *renderer, Bullet *bullet)
{
  apply_PhysicalObject(renderer, (PhysicalObject *)bullet);
}

void apply_Ship(SDL_Renderer *renderer, Ship *ship)
{
  //  (ship->exhaust_flames)->display();
  if(ship->banking == 0) apply_PhysicalObject(renderer, (PhysicalObject *)ship);
  if(ship->banking == -1) apply_PhysicalObject(renderer, (PhysicalObject *)ship, 1);
  if(ship->banking == -2) apply_PhysicalObject(renderer, (PhysicalObject *)ship, 3);
  if(ship->banking == 1) apply_PhysicalObject(renderer, (PhysicalObject *)ship, 2);
  if(ship->banking == 2) apply_PhysicalObject(renderer, (PhysicalObject *)ship, 4);

}



bool update_disp(SDL_Renderer *renderer, Image* background, Ship* myShip, std::vector<Bullet*> &bullets, std::vector<EnemyShip*> &enemies, std::vector<Bullet*> &enemy_bullets)
{
  SDL_RenderClear(renderer);
    //Apply the background to screen
  apply_texture( 0, 0, background->width, background->height, background->image, renderer, 0 );

    //Apply bullets to screen
    if(!bullets.empty())
    {
        for(std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++){
	  //            apply_texture(it->x, it->y, it->bullet_image, screen);
	  apply_Bullet(renderer, *it);
        }
    }

    //Apply Ship to screen
    apply_Ship(renderer, myShip);

    //Apply enemie bullets to screen
    if(!enemy_bullets.empty())
    {
        for(std::vector<Bullet*>::iterator it = enemy_bullets.begin(); it != enemy_bullets.end(); it++){
	  //           apply_texture(it->x, it->y, it->bullet_image, screen);
	  apply_PhysicalObject(renderer, *it);
        }
    }


    //Apply enemies to screen
    if(!enemies.empty())
    {
        for(std::vector<EnemyShip*>::iterator it = enemies.begin(); it != enemies.end(); it++){
	  //            apply_texture(it->x, it->y, it->enemy_image, screen);
	  apply_enemyShip(renderer, *it);
        }
    }

    //Update the screen
    SDL_RenderPresent(renderer);

    //SDL_UpdateWindowSurface(gWindow);
    return 1;
}
