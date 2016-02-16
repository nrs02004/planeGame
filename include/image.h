#ifndef airplaneGame_image_h
#define airplaneGame_image_h

#include "SDL2/SDL.h"
//#include "SDL/SDL_image.h"

class Image{
public:
  Image(SDL_Surface* init_image, float init_width, float init_height);
  ~Image();

  SDL_Surface* image;
  float width, height;
};

#endif
