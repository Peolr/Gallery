#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <Polygon.h>
#include <SDL.h>
#include <Scene.h>
class Polygon;
class Scene;
class Entity
{
    public:
        Entity(double x, double y);
        virtual ~Entity();

        double x;
        double y;

        double vy;
        double vx;

        double dx;
        double dy;

        bool frozen;

        double ox;
        double oy;

        double r;
        double scale;

        Scene* scene;

        std::vector<Polygon*> polygons;

        void render(SDL_Renderer* renderer);
        void update(double delta);
        void setScale(double s);
        void setRotation(double r);
        void addPolygon(Polygon* p);

    protected:

    private:
};

#endif // ENTITY_H
