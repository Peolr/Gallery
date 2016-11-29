#include "Polygon.h"
#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <cmath>



Polygon::Polygon(double x, double y)
{

    this->x = x;
    this->y = y;
    this->vx = 0;
    this->vy = 0;
    this->frozen = false;
    this->r = 0;

    for (int t = 0; t<4; t++)
    {
        this->color[t] = 255;
    }
    dx = 0;
    dy = 0;

    center = {0,0};


}

void Polygon::setCenter()
{


    double xMin=0.0;
    double yMin=0.0;
    double xMax=0.0;
    double yMax=0.0;
    for (int i = 0, m = points.size(); i < m; i++)
    {

        Vector2 p = points[i];

        if (p.x < xMin)
        {
            xMin = p.x;
        }

        if (p.y < yMin)
        {
            yMin = p.y;
        }

        if (p.x > xMax)
        {
            xMax = p.x;
        }

        if (p.y > yMax)
        {
            yMax = p.y;
        }

    }

    center = {(xMin+xMax)/2.0,(yMin+yMax)/2.0};

    this->xMin = xMin;
    this->yMin = yMin;
    this->xMax = xMax;
    this->yMax = yMax;

    reCalc();


}


void Polygon::reCalc()
{

    real.clear();

    for (int i = 0, m = points.size(); i < m; i++)
    {

        Vector2 p = Vector2(points[i].x,points[i].y);
        p.sub(center);
        p.rotate(r);
        p.add(center);
        real.insert(real.end(), p);

    }

}

void Polygon::addPoints(int argumentAmount, ... )
{


    if (argumentAmount % 2 == 0)
    {
        va_list arguments;
        va_start(arguments, argumentAmount);

        double parameter;
        for(int i = 0; i < argumentAmount-1; i=i+2 )
        {
            Vector2 p;
            parameter = va_arg(arguments, double);
            p.x = parameter;
            parameter = va_arg(arguments, double);
            p.y = parameter;
            points.insert(points.end(), p);
        }

        va_end(arguments);

        setCenter();

    }
}

Polygon::~Polygon()
{

}


void Polygon::render(SDL_Renderer* renderer)
{

    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);

    double x = this->x;
    double y = this->y;

    for (int i = 0, m=points.size(); i < m; i++)
    {
        int i2 = i + 1 == m ? 0 : i + 1;
        // get the current vertex
        Vector2 p1 = Vector2(points[i].x,points[i].y);
        // get the next vertex
        Vector2 p2 = Vector2(points[i2].x,points[i2].y);
        Vector2 pos = Vector2(x,y);


        p1.sub(center);
        p1.rotate(r);
        p1.add(pos);
        //p1.rotate(r);


        p2.sub(center);
        p2.rotate(r);
        p2.add(pos);
        // p2.rotate(r);



        SDL_RenderDrawLine(renderer, (p1.x), (p1.y), (p2.x), (p2.y));

        SDL_RenderDrawPoint(renderer, x,y);
    }
}

void Polygon::update(int delta)
{

    if (!frozen)
    {
        dx = x;
        dy = y;

        x += vx;
        y += vy;

        dx = x - dx;
        dy = y - dy;

    }
    else
    {

        dx = 0;
        dy = 0;

    }
    reCalc();


}

std::vector<Vector2> Polygon::getPoints()
{

    return real;

}

double dot(Vector2 a, Vector2 b)
{

    return (a.x*b.x + a.y*b.y);

}

Vector2 Polygon::getRealPos(Vector2 p)
{

    Vector2 ret = {(x - center.x + p.x), (y - center.y + p.y)};
    return ret;

}

std::vector<Vector2> Polygon::getRealPoints()
{
    std::vector<Vector2> ret;
    for (int i = 0, m = real.size(); i < m; i++)
    {
        ret.insert(ret.end(), getRealPos(real[i]));
    }
    return ret;

}

Vector2 Polygon::project(Vector2 axis)
{
    Vector2 d = real[0];
    d.add(Vector2(x,y));
    d.sub(center);
    double min = d.dot(axis);
    double max = min;
    for (int i = 1, m = real.size(); i < m; i++)
    {
        // NOTE: the axis must be normalized to get accurate projections
        Vector2 rp = real[i];
        rp.add(Vector2(x,y));
        rp.sub(center);
        double p = rp.dot(axis);
        if (p < min)
        {
            min = p;
        }
        else if (p > max)
        {
            max = p;
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

    //printf("o1: %9.6f\n",o);
    return o;

}

MTV Polygon::isColliding(Polygon shape2)
{
    std::vector<Vector2> axes1 = getAxes();
    std::vector<Vector2> axes2 = shape2.getAxes();

    double o = std::numeric_limits<double>::infinity();
    Vector2 sAxis = Vector2(0,0);
    bool flip;
// loop over the axes1
    for (int i = 0, m = axes1.size(); i < m; i++)
    {
        Vector2 axis = axes1[i];
        // project both shapes onto the axis
        Vector2 p1 = project(axis);
        Vector2 p2 = shape2.project(axis);
        // do the projections overlap?
        if (!overlap(p1, p2))
        {
            // then we can guarantee that the shapes do not overlap
            return MTV(Vector2(), -1);
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
        Vector2 p1 = project(axis);
        Vector2 p2 = shape2.project(axis);
        // do the projections overlap?
        if (!overlap(p1,p2))
        {
            // then we can guarantee that the shapes do not overlap
            return MTV(Vector2(), -1);
        }
        double ot = getOverlap(p1, p2, &flip);
        double ab = abs(ot);
        if (ab < o)
        {
            printf("ab: %9.6f, ot: %9.6f\n", ab, ot);
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

std::vector<Vector2> Polygon::getAxes()
{

    std::vector<Vector2> axes;
// loop over the vertices
    for (int i = 0, m = real.size(); i < m; i++)
    {
        // get the current vertex
        Vector2 p1 = real[i];//getRealPos(points[i]);
        // get the next vertex
        Vector2 p2 = real[i<m-1?i+1:0];//getRealPos(points[i + 1 == m ? 0 : i + 1]);

        Vector2 edge = Vector2(p2.x,p2.y);
        edge.sub(p1);
        // get either perpendicular vector
        edge.perp();
        edge.normalize();
        // the perp method is just (x, y) => (-y, x) or (y, -x)
        axes.insert(axes.end(), edge);
    }
    return axes;
}

