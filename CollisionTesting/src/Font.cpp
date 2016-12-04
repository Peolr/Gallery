#include "Font.h"


Font::Font(int i)
{
    w = 0;
    h = 0;
}

Font::~Font()
{
    //dtor
}



bool Font::free() {

    if (texture!=NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        w = 0;
        h = 0;
    }

}

bool Font::renderText(SDL_Renderer* renderer, std::string text, SDL_Color color, TTF_Font* gFont) {

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


bool Font::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
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

