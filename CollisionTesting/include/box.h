#ifndef BOX_H
#define BOX_H

#include <Polygon.h>


class Box : public Polygon
{
    public:
        Box(double x, double y, double w, double h);
        virtual ~Box();

    protected:

    private:
};

#endif // BOX_H
