#include "SAT.h"
#include <cstdio>

MTV checkCollision(Entity* a, Entity* b) {

    std::vector<Polygon*> polys = a->polygons;
    std::vector<Polygon*> polys2 = b->polygons;

    int max = 0;
    MTV res = MTV(false);

    for (int i = 0, m = polys.size(); i < m; i++) {
        for (int i2 = 0, m2 = polys2.size(); i2 < m2; i2++) {
            MTV cand = isColliding(polys[i], polys2[i2]);
            if (cand.collided && cand.o > max) {
                max = cand.o;
                res = cand;
            }
        }
    }
    return res;

}

MTV isColliding(Polygon* shape1, Polygon* shape2) {

    std::vector<Vector2> axes1 = shape1->getAxes();
    std::vector<Vector2> axes2 = shape2->getAxes();

    double o = std::numeric_limits<double>::infinity();
    Vector2 sAxis = Vector2(0,0);
    bool flip;
// loop over the axes1
    for (int i = 0, m = axes1.size(); i < m; i++)
    {
        Vector2 axis = axes1[i];
        // project both shapes onto the axis
        Vector2 p1 = projectPolygon(shape1, axis);
        Vector2 p2 = projectPolygon(shape2, axis);
        // do the projections overlap?
        if (!overlap(p1, p2))
        {
            // then we can guarantee that the shapes do not overlap
            return MTV(false);
        }

        double ot = getOverlap(p1, p2, &flip);
        double ab = fabs(ot);

        if (ab < o)
        {
            o = ab;
            sAxis.x = axis.x;
            sAxis.y = axis.y;
            if (ot < 0)
            {
                sAxis.reverse();
            }
        }

    }
// loop over the axes2
    for (int i = 0, m = axes2.size(); i < m; i++)
    {
        Vector2 axis = axes2[i];
        // project both shapes onto the axis
        Vector2 p1 = projectPolygon(shape1, axis);
        Vector2 p2 = projectPolygon(shape2, axis);
        // do the projections overlap?
        if (!overlap(p1,p2))
        {
            // then we can guarantee that the shapes do not overlap
            return MTV(false);
        }
        double ot = getOverlap(p1, p2, &flip);
        double ab = abs(ot);
        if (ab < o)
        {
            o = ab;
            sAxis.x = axis.x;
            sAxis.y = axis.y;
            if (ot < 0)
            {
                sAxis.reverse();
            }
        }
    }

    sAxis.scale(o);
// if we get here then we know that every axis had overlap on it
// so we can guarantee an intersection
    return MTV(sAxis,o);

}

Vector2 projectPolygon(Polygon* p, Vector2 axis) {

    //int x = p.x;
    //int y = p.y;

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

bool overlap (Vector2 a, Vector2 b)
{
    // printf("aMin: %i, aMax: %i, bMin: %i, bMax: %i\n", a.x, a.y, b.x, b.y);
    return !(a.y < b.x || b.y < a.x);
}

double getOverlap(Vector2 a, Vector2 b, bool* flip)
{

    double o = 0;

    if (a.x < b.x)
    {
        *flip = true;
        if (a.y < b.y)
        {
            o = a.y - b.x;
            *flip = false;
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
        *flip = false;
        if (a.y > b.y)
        {
            o = a.x - b.y;
            *flip = true;
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
