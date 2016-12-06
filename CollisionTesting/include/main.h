#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <Polygon.h>
#include <SDL_ttf.h>
#include <cstdio>
#include <JTexture.h>
#include <MTV.h>
#include <math.h>
#include <vector>
#include <SAT.h>
#include <sstream>
#include <SceneController.h>
#include <Box.h>
#include <Scene.h>
#include <Save.h>

int screenWidth = 600;
int screenHeight = 600;

SDL_Renderer* renderer;//Renderer
SDL_Window* window;//Window

SceneController* sc;

SDL_Event e;

bool renderTexture(SDL_Texture* t, int x, int y, int w, int h);
bool init();
bool loadMedia();


bool render();

void mouseClick();

TTF_Font *gFont;
Uint32 fps;
JTexture f;
//Variables for the mouse positions!
int mouseX;
int mouseY;

#endif // MAIN_H
