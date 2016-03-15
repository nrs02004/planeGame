#include "physicalObject.h"
#include <string>
#include <iostream>

PhysicalObject::PhysicalObject(float init_x, float init_y, std::vector<Image*> *init_images, Color _color, std::vector<Hitbox> _hitboxes)
{
  x = init_x;
  y = init_y;
  my_images = init_images;
  color = _color;
  angle = 0;
  hitboxes = _hitboxes;
}

PhysicalObject::PhysicalObject(float init_x, float init_y, Image *init_image, Color _color)
{
  x = init_x;
  y = init_y;
  my_images = new std::vector<Image*>;
  my_images->push_back(init_image);
  color = _color;
  angle = 0;
  hitboxes.push_back(Hitbox(0.0,4,4.0));
}

PhysicalObject::PhysicalObject(float init_x, float init_y, Image *init_image, Color _color, std::vector<Hitbox> _hitboxes)
{
  x = init_x;
  y = init_y;
  my_images = new std::vector<Image*>;
  my_images->push_back(init_image);
  color = _color;
  angle = 0;
  hitboxes = _hitboxes;
}
