#include "Polygon.h"
#include <SDL.h>
#include <stdio.h>
struct Vector2
{
    float x;
    float y;
};


Polygon::Polygon(float x, float y)
{

    this->x = x;
    this->y = y;
    this->vx = 0;
    this->vy = 0;
    this->frozen = false;

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


    int xMin=0;
    int yMin=0;
    int xMax=0;
    int yMax=0;
    for (int i = 0, m = points.size(); i < m; i++)
    {

        SDL_Point p = points[i];

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

    center = {(xMin+xMax)/2,(yMin+yMax)/2};

    //printf("mins: %i,%i, maxs: %i,%i\n", xMin,yMin,xMax,yMax);


}

void Polygon::addPoints(int argumentAmount, ... )
{

    if (argumentAmount % 2 == 0)
    {
        va_list arguments;
        va_start(arguments, argumentAmount);

        int parameter;
        for(int i = 0; i < argumentAmount-1; i=i+2 )
        {
            SDL_Point p;
            parameter = va_arg(arguments, int);
            p.x = parameter;
            parameter = va_arg(arguments, int);
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

    int x = this->x;
    int y = this->y;

    // printf("%i\n",y);

    for (int i = 0, m=points.size(); i < m; i++)
    {
        // get the current vertex
        SDL_Point p1 = points[i];
        // get the next vertex
        SDL_Point p2 = points[i + 1 == m ? 0 : i + 1];

        SDL_RenderDrawLine(renderer, (x - center.x + p1.x), (y - center.y + p1.y), (p2.x + x - center.x), (p2.y + y - center.y));

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

}

std::vector<SDL_Point> Polygon::getPoints()
{

    return points;

}

double dot(SDL_Point a, SDL_Point b)
{

    return (a.x*b.x + a.y*b.y);

}

SDL_Point Polygon::getRealPos(SDL_Point p) {

    SDL_Point ret = {(x - center.x + p.x), (y - center.y + p.y)};
    return ret;

}

SDL_Point Polygon::project(SDL_Point axis)
{
    double min = dot(axis,getRealPos(points[0]));
    double max = min;
    for (int i = 1, m = points.size(); i < m; i++)
    {
        // NOTE: the axis must be normalized to get accurate projections
       // printf("axis x: %i, axis y: %i\n", axis.x, axis.y);

        double p = dot(axis, getRealPos(points[i]));
        //printf("dot: %9.6f\n", p);
        if (p < min)
        {
            min = p;
        }
        else if (p > max)
        {
            max = p;
        }
    }
    SDL_Point proj = {min, max};
    return proj;
}

bool overlap (SDL_Point a, SDL_Point b) {
   // printf("aMin: %i, aMax: %i, bMin: %i, bMax: %i\n", a.x, a.y, b.x, b.y);
    return ((b.x < a.y && b.y > a.x) || (b.y > a.x && b.x < a.x));
}

bool Polygon::isColliding(Polygon shape2)
{
    std::vector<SDL_Point> axes1 = getAxes();
    std::vector<SDL_Point> axes2 = shape2.getAxes();
// loop over the axes1
    for (int i = 0, m = axes1.size(); i < m; i++)
    {
        SDL_Point axis = axes1[i];
        // project both shapes onto the axis
        SDL_Point p1 = project(axis);
        SDL_Point p2 = shape2.project(axis);
        // do the projections overlap?
        if (!overlap(p1, p2))
        {
            // then we can guarantee that the shapes do not overlap
            return false;
        }
    }
// loop over the axes2
    for (int i = 0, m = axes2.size(); i < m; i++)
    {
        SDL_Point axis = axes2[i];
        // project both shapes onto the axis
        SDL_Point p1 = project(axis);
        SDL_Point p2 = shape2.project(axis);
        // do the projections overlap?
        if (!overlap(p1,p2))
        {
            // then we can guarantee that the shapes do not overlap
            return false;
        }
    }
// if we get here then we know that every axis had overlap on it
// so we can guarantee an intersection
    return true;


}

std::vector<SDL_Point> Polygon::getAxes()
{

    std::vector<SDL_Point> axes;
// loop over the vertices
    for (int i = 0, m = points.size(); i < m; i++)
    {
        // get the current vertex
        SDL_Point p1 = getRealPos(points[i]);
        // get the next vertex
        SDL_Point p2 = getRealPos(points[i + 1 == m ? 0 : i + 1]);

       // printf("p1Edge x: %i edge y: %i\n", p1, p1.y);
       // printf("p2Edge x: %i edge y: %i\n", p2.x, p2.y);
        // subtract the two to get the edge vector
        SDL_Point edge = {p1.x-p2.x,p1.y-p2.y};
        // get either perpendicular vector
        SDL_Point normal = {edge.x,-edge.y};
        // the perp method is just (x, y) => (-y, x) or (y, -x)
        axes.insert(axes.end(), normal);
    }
    return axes;
}

