#ifndef MTV_H
#define MTV_H

#include <Vector2.h>

class MTV
{
    public:
        MTV(Vector2 axis, double o);
        virtual ~MTV();
        Vector2 axis;
        double o;

    protected:

    private:
};

#endif // MTV_H
