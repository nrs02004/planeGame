#include "physicalObject.h"
#include <string>
#include <iostream>

PhysicalObject::PhysicalObject(float init_x, float init_y, std::vector<Image*> *init_images)
{
  x = init_x;
  y = init_y;
  my_images = init_images;
}

PhysicalObject::PhysicalObject(float init_x, float init_y, Image *init_image)
{
  x = init_x;
  y = init_y;
  my_images = new std::vector<Image*>;
  my_images->push_back(init_image);
}
