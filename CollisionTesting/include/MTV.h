#ifndef MTV_H
#define MTV_H

#include <Vector2.h>

class MTV
{
    public:
        MTV(Vector2 axis, double o);
        MTV(bool f);
        virtual ~MTV();

        Vector2 axis;
        double o;
        bool collided;

    protected:

    private:
};

#endif // MTV_H
