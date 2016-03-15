#ifndef __airplaneGame__physicalObject__
#define __airplaneGame__physicalObject__


#include "image.h"
#include <vector>
#include "color.h"
#include "hitbox.h"

class PhysicalObject{
public:
  PhysicalObject(float init_x, float init_y, std::vector<Image*> *init_images, Color _color, std::vector<Hitbox>);
  PhysicalObject(float init_x, float init_y, Image* init_image, Color _color);
  PhysicalObject(float init_x, float init_y, Image* init_image, Color _color, std::vector<Hitbox>);

  float x,y;
  Color color;
  std::vector<Image*> *my_images;
  double angle;

  std::vector<Hitbox> hitboxes;
};

#endif
