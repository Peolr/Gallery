#ifndef BOX_H
#define BOX_H

#include <SDL.h>
#include <vector>

class box
{
public:
    box(float x, float y, int w, int h);
    virtual ~box();

    float x;
    float y;
    int w;
    int h;

    float vx;
    float vy;

    float dx;
    float dy;

    bool frozen;

    int color[4];

    SDL_Rect rect;

    void render(SDL_Renderer* renderer);
    void setRect();
    void update(int delta);

    std::vector<SDL_Point> getPoints();

protected:

private:
};

#endif // BOX_H
