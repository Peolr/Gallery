#include "box.h"
#include <SDL.h>



box::box(float x, float y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->vx = 0;
    this->vy = 0;
    this->frozen = false;

    for (int t = 0; t<4; t++) {
        this->color[t] = 255;
    }

    setRect();

    dx = 0;
    dy = 0;
}

box::~box()
{
    //dtor
}

void box::setRect() {
    rect = {x,y,w,h};


}

void box::render(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_RenderDrawRect(renderer, &rect);

}

void box::update(int delta) {

    dx = x;
    dy = y;

    x += vx;
    y += vy;

    dx = x - dx;
    dy = y - dy;

    setRect();

}

std::vector<SDL_Point> box::getPoints() {

    std::vector<SDL_Point> points;

    SDL_Point center = {x+w/2,y+h/2};



    points.insert(points.end(), {center.x - w/2, center.y - h/2});
    points.insert(points.end(), {center.x + w/2, center.y - h/2});
    points.insert(points.end(), {center.x - w/2, center.y + h/2});
    points.insert(points.end(), {center.x + w/2, center.y + h/2});

    return points;

}

