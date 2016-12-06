#include "Polygon.h"
#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <cmath>



Polygon::Polygon(double x, double y)
{
    setup(x,y);
}

Polygon::Polygon() {
    setup(0,0);
}

void Polygon::setup(double x, double y) {

    this->x = x;
    this->y = y;
    this->frozen = false;
    this->r = 0;
    scale = 1.0;

    for (int t = 0; t<4; t++)
    {
        this->color[t] = 255;
    }
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

        Vector2 p = Vector2(points[i].x, points[i].y).scale(scale);

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

}

void Polygon::clearPoints() {
    points.clear();
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

    for (int i = 0, m=points.size(); i < m; i++)
    {
        int i2 = i + 1 == m ? 0 : i + 1;
        // get the current vertex
        Vector2 p1 = Vector2(points[i].x,points[i].y);
        // get the next vertex
        Vector2 p2 = Vector2(points[i2].x,points[i2].y);

        p1 = getRealPos(p1);
        p2 = getRealPos(p2);

        SDL_RenderDrawLine(renderer, (p1.x), (p1.y), (p2.x), (p2.y));

        SDL_RenderDrawPoint(renderer, x,y);
    }
}

void Polygon::update(int delta)
{
}

Vector2 Polygon::getRealPos(Vector2 p)
{

    double zoom = parent->scene->zoom/100.0;
    double scale = parent->scale*zoom;

    double cameraX = parent->scene->cameraX;
    double cameraY = parent->scene->cameraY;

    Vector2 org = Vector2(parent->ox, parent->oy).scale(scale);
    Vector2 px = Vector2(parent->x - cameraX,parent->y - cameraY);
    Vector2 pos = Vector2(x, y).scale(scale);

    p.scale(scale);
    p.add(pos);
    p.sub(org);
    p.rotate(parent->r);
    p.add(org);
    //do center here?
    //p.rotate(r);
    p.add(px);
    return p;

}


std::vector<Vector2> Polygon::getAxes()
{

    std::vector<Vector2> axes;
// loop over the vertices
    for (int i = 0, m = points.size(); i < m; i++)
    {
        // get the current vertex
        Vector2 p1 = getRealPos(Vector2(points[i].x, points[i].y));//getRealPos(points[i]);
        // get the next vertex
        int i2 = i<m-1?i+1:0;

        Vector2 p2 = getRealPos(Vector2(points[i2].x, points[i2].y));//getRealPos(points[i + 1 == m ? 0 : i + 1]);

        Vector2 edge = Vector2(p2.x,p2.y);
        edge.sub(p1);
        edge.perp();
        edge.normalize();
        axes.insert(axes.end(), edge);
    }
    return axes;
}

