#ifndef airplaneGame_image_h
#define airplaneGame_image_h



#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

class Image{
public:
  Image(SDL_Texture* init_image, float init_width, float init_height);
  ~Image();

  SDL_Texture* image;
  double angle;
  float width, height;
};

#endif
