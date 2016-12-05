#ifndef POLYGON_H
#define POLYGON_H

#include <SDL.h>
#include <Vector2.h>
#include <vector>
#include <MTV.h>
#include <Entity.h>
class Entity;

class Polygon
{
public:
    Polygon(double x, double y);
    Polygon();
    virtual ~Polygon();

    double x;
    double y;

    double r;

    double vx;
    double vy;

    double dx;
    double dy;

    double scale;

    double xMin, xMax, yMin, yMax;

    bool frozen;

    int color[4];

    Vector2 center;

    Entity* parent;

    void setup(double x, double y);
    void render(SDL_Renderer* renderer, double ddx = 0.0, double ddy = 0.0, double ox = 0.0, double oy = 0.0, double zoom = 1.0);
    void update(int delta);

    std::vector<Vector2> points;

    std::vector<Vector2> getPoints();
    void addPoints( int argumentAmount, ... );
    void clearPoints();
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
