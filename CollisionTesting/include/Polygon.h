#ifndef POLYGON_H
#define POLYGON_H

#include <SDL.h>
#include <vector>


class Polygon
{
public:
    Polygon(float x, float y);
    virtual ~Polygon();

    float x;
    float y;

    float vx;
    float vy;

    float dx;
    float dy;

    bool frozen;

    int color[4];

    SDL_Point center;


    void render(SDL_Renderer* renderer);
    void update(int delta);

    std::vector<SDL_Point> points;

    std::vector<SDL_Point> getPoints();
    void addPoints( int argumentAmount, ... );

    void setCenter();

    std::vector<SDL_Point> getAxes();
    SDL_Point project(SDL_Point axis);
    bool isColliding(Polygon shape2);

    SDL_Point getRealPos(SDL_Point p);

protected:

private:
};

#endif // BOX_H
