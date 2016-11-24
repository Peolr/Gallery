#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <box.h>
#include <Polygon.h>

struct Vector2
{
  float x;
  float y;
};

SDL_Renderer* renderer;//Renderer
SDL_Window* window;//Window
SDL_Texture* background;//3x3 grid

SDL_Texture* loadTexture(std::string s);

bool renderTexture(SDL_Texture* t, int x, int y, int w, int h);
bool init();
bool loadMedia();
bool render();

void mouseClick();

#endif // MAIN_H
