#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <cstdio>

class Font
{
    public:
        Font(int i);
        virtual ~Font();

        SDL_Texture* texture;
        int w;
        int h;


        bool free();
        bool renderText(SDL_Renderer* renderer,  std::string text, SDL_Color color, TTF_Font* gFont);
        bool render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    protected:

    private:
};

#endif // FONT_H
