#include "SAT.h"
#include <cstdio>

//Take all polygons of both entities and check for collision. Get the biggest move vector to find the furthest vector to push it away with.
MTV checkCollision(Entity* a, Entity* b)
{

    std::vector<Polygon*> polys = a->polygons;
    std::vector<Polygon*> polys2 = b->polygons;

    int max = 0;
    MTV res = MTV(false);

    //We need to loop thru every single polygon in both entities!
    for (int i = 0, m = polys.size(); i < m; i++)
    {
        for (int i2 = 0, m2 = polys2.size(); i2 < m2; i2++)
        {
            MTV cand = isColliding(polys[i], polys2[i2]);
            if (cand.collided && cand.o > max)
            {
                max = cand.o;
                res = cand;
            }
        }
    }
    return res;

}

//Loop through all axes of a polygon, and project all the points of both polygons and calculate if they overlap. If they don't we automagically know it doesn't collide.
bool loopThruAxes(std::vector<Vector2> axes, Polygon* shape1, Polygon* shape2, double* o, Vector2* sAxis)
{

    for (int i = 0, m = axes.size(); i < m; i++)
    {
        Vector2 axis = axes[i];
        // project both shapes onto the axis
        Vector2 p1 = projectPolygon(shape1, axis);
        Vector2 p2 = projectPolygon(shape2, axis);
        // do the projections overlap?
        if (!overlap(p1, p2))
        {
            // then we can guarantee that the shapes do not overlap
            return true;
        }

        double ot = getOverlap(p1, p2);
        double ab = fabs(ot);

        if (ab < *o)
        {
            *o = ab;
            sAxis->x = axis.x;
            sAxis->y = axis.y;
            if (ot < 0)
            {
                sAxis->reverse();
            }
        }

    }

    return false;
}

//Are we colliding? If so return MTV!
MTV isColliding(Polygon* shape1, Polygon* shape2)
{

    std::vector<Vector2> axes1 = shape1->getAxes();
    std::vector<Vector2> axes2 = shape2->getAxes();

    double o = std::numeric_limits<double>::infinity();
    Vector2 sAxis = Vector2(0,0);

    bool notCollide = !(!loopThruAxes(axes1, shape1, shape2, &o, &sAxis) && !loopThruAxes(axes2, shape1, shape2, &o, &sAxis));

    //no intersection occurred
    if (notCollide) {
        return MTV(false);
    }

    //Scale direction for o distance
    sAxis.scale(o);
    return MTV(sAxis,o);

}

//Takes a polygon, and loops through points and "projects" all points onto a plane and returns a min and a max,
//we will use this to determine an overlap later on.
Vector2 projectPolygon(Polygon* p, Vector2 axis)
{

    Vector2 d = p->getRealPos(Vector2(p->points[0].x, p->points[0].y));
    double min = d.dot(axis);
    double max = min;
    for (int i = 1, m = p->points.size(); i < m; i++)
    {
        // NOTE: the axis must be normalized to get accurate projections
        Vector2 rp = p->getRealPos(Vector2(p->points[i].x,p->points[i].y));
        //printf("p.y: %i, parenty: %9.6f\n", y, p.parent->y);
        double dot = rp.dot(axis);
        if (dot < min)
        {
            min = dot;
        }
        else if (dot > max)
        {
            max = dot;
        }
    }
    Vector2 proj = {min, max};
    return proj;

}

//Do both mins and maxes overlap?
bool overlap (Vector2 a, Vector2 b)
{
    //Check if they don't overlap, and send the opposite
    return !(a.y < b.x || b.y < a.x);
}

//Find the best "overlap" in 2 vectors.
double getOverlap(Vector2 a, Vector2 b)
{

    double o = 0;

    if (a.x < b.x)
    {
        if (a.y < b.y)
        {
            o = a.y - b.x;
        }
        else
        {
            double one = a.y - b.x;
            double two = b.y - a.x;
            o = one < two ? one : -two;
        }
    }
    else
    {
        if (a.y > b.y)
        {
            o = a.x - b.y;
        }
        else
        {
            double one = a.y - b.x;
            double two = b.y - a.x;
            o = one < two ? one : -two;
        }
    }
    return o;
}
