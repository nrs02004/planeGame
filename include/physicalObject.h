#ifndef __airplaneGame__physicalObject__
#define __airplaneGame__physicalObject__


#include "image.h"
#include <vector>

class PhysicalObject{
public:
  PhysicalObject(float init_x, float init_y, std::vector<Image*> *init_images);
  PhysicalObject(float init_x, float init_y, Image* init_image);

    float x,y;
    std::vector<Image*> *my_images;
};

#endif
