#ifndef HELLO_H_INCLUDED
#define HELLO_H_INCLUDED

#include <string>
#include <button.h>

SDL_Renderer* renderer;//Renderer
SDL_Window* window;//Window
SDL_Texture* background;//3x3 grid
SDL_Texture* xMark;//x
SDL_Texture* oMark;//o

SDL_Texture* loadTexture(std::string s);

bool renderTexture(SDL_Texture* t, int x, int y, int w, int h);
bool init();
bool loadMedia();
bool render();

int checkWin();

void mouseClick();

#endif // HELLO_H_INCLUDED
