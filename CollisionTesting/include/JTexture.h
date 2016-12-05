#ifndef JTEXTURE_H
#define JTEXTURE_H

#include <Font.h>


#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <cstdio>

class JTexture
{
    public:
        JTexture();
        virtual ~JTexture();

        SDL_Texture* texture;
        int w;
        int h;


        bool free();

        bool loadTexture(SDL_Renderer* renderer, std::string s);
        bool renderText(SDL_Renderer* renderer,  std::string text, SDL_Color color, TTF_Font* gFont);

        bool render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        void setSize(int ww, int hh);

    protected:

    private:
};

#endif // JTEXTURE_H
