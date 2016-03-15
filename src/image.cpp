#include"image.h"

Image::Image(SDL_Texture* init_image, float init_width, float init_height)
{
  image = init_image;
  width = init_width;
  height = init_height;
}

Image::~Image()
{
  SDL_DestroyTexture(image);
}
