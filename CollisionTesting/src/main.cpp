#include "main.h"
#include <SDL.h>
#include <cstdio>
#include <MTV.h>
#include <math.h>
#include <vector>
#include <SAT.h>

//Boolean to check if we should quit the program (press the x button)
bool quit;

//Screen width and height set as constants!
const int screenWidth = 600;
const int screenHeight = 600;

//Variables for the mouse positions!
int mouseX;
int mouseY;

box b(20, 20, 40, 40);
box b2(0, 400, 400, 40);

void collisiontest(box& b, box& b2);


Polygon p(150.0,150.0);
Polygon p2(25.0,25.0);
std::vector<Vector2> p3;

SAT Collision = SAT();


//Main function
int main( int argc, char* args[] )
{

    //Does initialization return true?
    if (init())
    {

        //We don't want to quit!
        quit = false;

        //SDL Event Poller
        SDL_Event e;

        Uint32 countedFrames = 0;//How many frames have we counted in the last second?
        Uint8 ticksPerFrame = 1000/60;//Framerate
        Uint32 startTick = SDL_GetTicks(); //The tick we started counting frames
        Uint32 nextFrame = startTick;//The next tick that we should render the next frame
        Uint32 curTick;//The current tick we are on!
        //time between frames
        float delta = 1;
        Uint32 lastTick = startTick;

        b2.frozen = true;

        double s = 25.0;
        int sc = 3;
       // p.addPoints((6*2), 99, 200,310, 218,253, 3,46, 0,0, 66,35, 155);//((3*2), 0,0, s,0, s,s );
        p2.addPoints((3*2), 0.0,0.0, s,0.0, s,s );
        p.addPoints((3*2), 0.0,0.0, s,0.0, s,s );



        //Main game loop
        while (!quit)
        {

            //Set the current tick
            curTick = SDL_GetTicks();

            //Go through all of the events since last run-through!
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type==SDL_QUIT)   //Did we close the game?
                {
                    quit = true;
                }
                else if (e.type==SDL_MOUSEBUTTONDOWN)     //Was the mouse pressed once?
                {
                    mouseClick();
                }
            }

            //Find the mouse position relative to the window, and set it to mouseX and mouseY.
            SDL_GetMouseState(&mouseX, &mouseY);

            const Uint8* keyStates = SDL_GetKeyboardState(NULL);

            if (keyStates[SDL_SCANCODE_D])
            {
                b.vx = 10;
            }
            else if (keyStates[SDL_SCANCODE_A])
            {
                b.vx = -10;
            }
            else
            {
                b.vx = 0;
            }

            //Has enough time passed to render the next frame?
            if (curTick>=nextFrame)
            {
                delta = (curTick - lastTick)/1000.0;
                lastTick = curTick;

                nextFrame = curTick+ticksPerFrame;
                countedFrames++;
                //Has it been a second? Print the fps!
                if (startTick+1000 < SDL_GetTicks())
                {
                    printf("FPS : %i\n",countedFrames);
                    countedFrames = 0;
                    startTick = SDL_GetTicks();
                }

                double speed = 50;

                const Uint8 *keys = SDL_GetKeyboardState(NULL);
                if (keys[SDL_SCANCODE_D])
                {
                    p2.x += speed * delta;
                }
                else if (keys[SDL_SCANCODE_A])
                {
                    p2.x -= speed * delta;
                }

                if (keys[SDL_SCANCODE_S])
                {
                    p2.y += speed * delta;
                }
                else if (keys[SDL_SCANCODE_W])
                {
                    p2.y -= speed * delta;
                }

                if (keys[SDL_SCANCODE_E]) {
                    p2.r+=1*delta;
                } else if(keys[SDL_SCANCODE_Q]) {
                    p2.r-=1*delta;
                }


                b.update(delta);
                b2.update(delta);

                p.update(delta);
                p2.update(delta);

                b.vy += delta * 9.8;
                //p2.vx = .5;
                MTV tt = Collision.checkCollision(p2, p);
                if (tt.collided)
                {
                   // printf("o: %9.6f\n", tt.o);
                    p2.x -= tt.axis.x;
                    p2.y -= tt.axis.y;
                    // printf("colliding true!\n");
                }
                else
                {
                    // printf("not colliding!\n");
                }
                // b.x = mouseX - b.w/2;
                //b.y = mouseY - b.h/2;

               // p.r+=0.174533*delta;





                collisiontest(b, b2);

                b.setRect();

                std::vector<SDL_Point> e = b.getPoints();

                for (SDL_Point p : e)
                {
                    //printf("x: %i, y: %i\n", p.x, p.y);
                }

                p3.clear();

                std::vector<Vector2> points1 = p.getRealPoints();
                std::vector<Vector2> points2 = p2.getRealPoints();
                for (int i = 0, m = points1.size(); i < m; i++) {

                    for (int u = 0, mu = points2.size(); u < mu; u++) {
                        double x = (points1[i].x - points2[u].x) + 25;
                        double y = (points1[i].y - points2[u].y) + 25;
                        p3.insert(p3.end(), Vector2(x,y));
                       // printf("%9.6f : %9.6f\n",x,y);
                    }

                }

              //  printf("%i size\n", p3.points.size());


                render();
                // SDL_Delay(ticksPerFrame);
            }


        }

    }
    else
    {
        printf("Failed to initialize!");
    }

    //Deallocate and quit!
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

void collisiontest(box& b1, box& b2)
{

    if (((b1.x < b2.x + b2.w) && (b1.y < b2.y + b2.h)) && ((b2.x < b1.x + b1.w) && (b2.y < b1.y + b1.h)))
    {
        // printf("collide!\n");
        if (b1.y + b1.h > b2.y)
        {
            if (b1.dy > 0)
            {
                b1.y -= (b1.y+b1.h)-b2.y;;
            }
            else if (b1.dy < 0)
            {
                b1.y += (b2.y + b2.h) - b1.y;
            }
            b1.vy = 0;
        }
    }



}


bool init()
{


    bool success = true;

    //Init video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize video! %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Make window
        window = SDL_CreateWindow("Test window!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if (window==NULL)
        {
            printf("Could not create window! %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Make renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer==NULL)
            {
                printf("Could not create renderer! %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}

//Load a texture from a string and return the created texture!
SDL_Texture* loadTexture(std::string s)
{
    SDL_Surface* loadedSurface = IMG_Load(s.c_str());
    if (loadedSurface==NULL)
    {
        printf("Could not load image! %s\n", IMG_GetError());
        SDL_FreeSurface(loadedSurface);
    }
    else
    {

        //Convert Surface to Texture!
        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        //Allow for alpha in png!
        SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
        SDL_FreeSurface(loadedSurface);
        return newTexture;
    }
    return NULL;
}

//Render a texture with position and size
bool renderTexture(SDL_Renderer* r, SDL_Texture* t, int x, int y, int w, int h)
{

    SDL_Rect rect = {x,y,w,h};
    SDL_RenderCopy(r, t, NULL, &rect);

    return true;
}



//Calculate clicks
void mouseClick()
{
}


bool render()
{
    SDL_RenderClear(renderer); // Clear our screen



    //b.render(renderer);
    //b2.render(renderer);
    p.render(renderer);
    p2.render(renderer);
    for (int i = 0, m=p3.size(); i < m; i++)
    {
        int i2 = i + 1 == m ? 0 : i + 1;
        // get the current vertex
        Vector2 p1 = Vector2(p3[i].x,p3[i].y);
        // get the next vertex
        Vector2 p2 = Vector2(p3[i2].x,p3[i2].y);
        //Vector2 pos = Vector2(x,y);




        SDL_RenderDrawLine(renderer, (p1.x), (p1.y), (p2.x), (p2.y));

       // SDL_RenderDrawPoint(renderer, x,y);
    }

    SDL_RenderDrawPoint(renderer, 25, 25);

    //SDL_RenderDrawPoint(renderer, p.x + p2.x, p.y + p2.y);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //Present our screen to the window!
    SDL_RenderPresent(renderer);

    return true;
}
