#ifndef SAT_H
#define SAT_H

#include <Polygon.h>
#include <Vector2.h>
#include <vector>
#include <limits>
#include <cmath>
#include <cstdlib>

double dot(Vector2 a, Vector2 b);
bool overlap (Vector2 a, Vector2 b);
double getOverlap(Vector2 a, Vector2 b, bool* flip);

class SAT
{
    public:
        SAT();
        MTV checkCollision(Polygon a, Polygon b);
        MTV isColliding(Polygon a, Polygon b);
        Vector2 projectPolygon(Polygon p, Vector2 axis);


    protected:

    private:
};

#endif // SAT_H
