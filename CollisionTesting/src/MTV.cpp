#include "MTV.h"

MTV::MTV(Vector2 axis, double o)
{
    this->axis = axis;
    this->o = o;
    collided = true;
}

MTV::MTV(bool f) {
    collided = false;
}

MTV::~MTV()
{

}
