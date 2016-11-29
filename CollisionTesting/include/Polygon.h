#ifndef POLYGON_H
#define POLYGON_H

#include <SDL.h>
#include <Vector2.h>
#include <vector>
#include <MTV.h>


class Polygon
{
public:
    Polygon(double x, double y);
    virtual ~Polygon();

    double x;
    double y;

    double r;

    double vx;
    double vy;

    double dx;
    double dy;

    double xMin, xMax, yMin, yMax;

    bool frozen;

    int color[4];

    Vector2 center;


    void render(SDL_Renderer* renderer);
    void update(int delta);

    std::vector<Vector2> points;

    std::vector<Vector2> getPoints();
    void addPoints( int argumentAmount, ... );

    void setCenter();

    std::vector<Vector2> getAxes();
    Vector2 project(Vector2 axis);
    MTV isColliding(Polygon shape2);

    Vector2 getRealPos(Vector2 p);
    std::vector<Vector2> real;
    std::vector<Vector2> getRealPoints();

    void reCalc();

protected:

private:
};

#endif // BOX_H
