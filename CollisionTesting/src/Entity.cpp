#include "Entity.h"

#include <cstdio>

Entity::Entity(double x, double y)
{
    this->x = x;
    this->y = y;
    dx = 0.0;
    dy = 0.0;
    vx = 0.0;
    vy = 0.0;
    ox = 0.0;
    oy = 0.0;
    scale = 1;
}

Entity::~Entity()
{
    for (int i = 0, m = polygons.size(); i < m; i++) {
        delete polygons[i];
    }
    polygons.clear();
}

void Entity::setScale(double s) {
    scale = s;
    for (int i = 0, m = polygons.size(); i < m; i++) {
        polygons[i]->scale = s;
    }
}

void Entity::setRotation(double r) {
    this->r = r;
}

void Entity::render(SDL_Renderer* renderer) {
    for (int i = 0, m = polygons.size(); i < m; i++) {
        polygons[i]->render(renderer);
    }
}

void Entity::update(double delta)
{

    if (!frozen)
    {
        dx = x;
        dy = y;

        x += vx;
        y += vy;

        dx = x - dx;
        dy = y - dy;


        for (int i = 0, m = polygons.size(); i < m; i++) {
            polygons[i]->reCalc();
        }

    }
    else
    {

        dx = 0;
        dy = 0;

    }



}

void Entity::addPolygon(Polygon* p) {
    p->scale = scale;
    p->parent = this;
    polygons.insert(polygons.end(), p);
}
