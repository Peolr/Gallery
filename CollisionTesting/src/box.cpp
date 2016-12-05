#include "Box.h"

Box::Box(double x, double y, double w, double h) : Polygon(x,y)
{
    addPoints((4*2), 0.0,0.0, w,0.0, w,h, 0.0,h);
}

Box::~Box()
{
    //dtor
}
