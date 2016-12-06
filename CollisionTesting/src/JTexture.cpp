#include "JTexture.h"

#include <SDL_image.h>
#include <SDL.h>

JTexture::JTexture()
{
    w = 0;
    h = 0;
}

JTexture::~JTexture()
{
    //dtor
}



bool JTexture::free() {

    if (texture!=NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        w = 0;
        h = 0;
    }
    return true;
}

bool JTexture::loadTexture(SDL_Renderer* renderer, std::string s) {
    SDL_Surface* loadedSurface = IMG_Load(s.c_str());
    free();
    if (loadedSurface==NULL)
    {
        printf("Could not load image! %s\n", IMG_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }
    else
    {

        //Convert Surface to Texture!
        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        //Allow for alpha in png!
        SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
        SDL_FreeSurface(loadedSurface);
        texture = newTexture;
    }
    return true;
}

//Turns the texture into text with string and color with font.
bool JTexture::renderText(SDL_Renderer* renderer, std::string text, SDL_Color color, TTF_Font* gFont) {

    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);
    if (textSurface == NULL) {

        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    } else {


        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        w = textSurface->w;
        h = textSurface->h;
        SDL_FreeSurface(textSurface);
    }
    return true;
}

//render the texture
bool JTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, w, h };
	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );

	return true;
}

void JTexture::setSize(int ww, int hh) {
    w = ww;
    h = hh;
}
