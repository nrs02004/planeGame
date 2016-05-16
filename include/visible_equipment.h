#ifndef __airplaneGame__visible_equipment__
#define __airplaneGame__visible_equipment__


#include "image.h"
#include <vector>
#include "color.h"

class Visible_equipment{
public:
    Visible_equipment(){};
  Visible_equipment(float*, float*, Image*, Color);

  float *x_ptr, *y_ptr;
  Color color;
  Image *my_image;
  double angle;
};

class Shield : public Visible_equipment
{
public:
    Shield(){length = -1.0; active = false;}; //Default to check if there's a shield
    Shield(float*, float*, Image*, Color);
    void activate();
    void update(float);
    float length, remaining;
    bool active;
    Color max_color;
};

#endif