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

    double scale;

    double xMin, xMax, yMin, yMax;

    bool frozen;

    int color[4];

    Vector2 center;

    Entity* parent;

    void setup(double x, double y);
    void render(SDL_Renderer* renderer);
    void update(int delta);

    std::vector<Vector2> points;

    void addPoints( int argumentAmount, ... );
    void clearPoints();
    void setCenter();

    std::vector<Vector2> getAxes();

    Vector2 getRealPos(Vector2 p);


protected:

private:
};

#endif // BOX_H
