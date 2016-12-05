#include "main.h"
//Boolean to check if we should quit the program (press the x button)
bool quit;


JTexture happy;

//Main function
int main( int argc, char* args[] )
{

    //Does initialization return true?
    if (init() && loadMedia())
    {

        Scene* scene = sc->newScene();

        Entity* ent = new Entity(0.0, 300.0);
        Entity* ent2 = new Entity(0.0, 400.0);

        Box poly(0.0,0.0,30.0,30.0);
        Box poly2(30.0,0.0,30.0,30.0);
        ent->addPolygon(poly);
        ent->addPolygon(poly2);




        Box poly22(0.0,0.0,600.0,30.0);
        ent2->addPolygon(poly22);


        scene->addEntity(ent2);
        scene->addEntity(ent);

        //We don't want to quit!
        quit = false;
        fps = 0;


        Uint32 countedFrames = 0;//How many frames have we counted in the last second?
        Uint8 ticksPerFrame = 1000/60;//Framerate
        Uint32 startTick = SDL_GetTicks(); //The tick we started counting frames
        Uint32 nextFrame = startTick;//The next tick that we should render the next frame
        Uint32 curTick;//The current tick we are on!
        //time between frames
        float delta = 1;
        Uint32 lastTick = startTick;

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
                    fps = countedFrames;
                    countedFrames = 0;
                    startTick = SDL_GetTicks();
                }








                //Entity* ent = sc->getCurrentScene()->entities[0];
                Scene* sce = sc->getCurrentScene();


                double speed = 50.0;

                const Uint8 *keys = SDL_GetKeyboardState(NULL);
                if (keys[SDL_SCANCODE_D])
                {
                    ent->x += speed * delta;
                }
                else if (keys[SDL_SCANCODE_A])
                {
                    ent->x -= speed * delta;
                }

                if (keys[SDL_SCANCODE_S])
                {
                    //ent->y += speed * delta;
                }
                else if (keys[SDL_SCANCODE_W])
                {
                    ent->vy = -200*delta;

                }

                if (keys[SDL_SCANCODE_E]) {
                    //ent->setRotation(ent->r + 1*delta);
                } else if(keys[SDL_SCANCODE_Q]) {
                    //ent->setRotation(ent->r - 1*delta);
                }

                sce->update(delta);

                printf("Dy: %9.6f\n", ent->dy);

                if (ent->dy == 0.0) {
                    ent->vy = 0;
                }

                ent->vy+=9.8*delta;


                /**/
                MTV collide = checkCollision(ent, ent2);

                if (collide.collided) {
                    ent->x-=collide.axis.x;
                    ent->y-=collide.axis.y;
                    //printf("collide\n");
                }
                /**/
                printf("entx: %9.6f\n", ent->polygons[0].x + ent->x);

                //Entity* ent = sc.getCurrentScene()->entities[0];
                //ent->setRotation((curTick*delta*.2) );


/*minsowski difference i wanna test with stuff of this later
                std::vector<Vector2> points1 = p.getRealPoints();
                std::vector<Vector2> points2 = p2.getRealPoints();
                for (int i = 0, m = points1.size(); i < m; i++) {
                    for (int u = 0, mu = points2.size(); u < mu; u++) {
                        double x = (points1[i].x - points2[u].x) + 25;
                        double y = (points1[i].y - points2[u].y) + 25;
                        p3.insert(p3.end(), Vector2(x,y));
                       // printf("%9.6f : %9.6f\n",x,y);
                    }

                }*/


                render();
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
    renderer = NULL;
    window = NULL;

    f.free();
    delete(sc);
    sc = NULL;

    TTF_CloseFont(gFont);
    gFont = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

bool init()
{

    bool success = true;
    sc = new SceneController();
    //Init video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize video! %s\n", SDL_GetError());
        success = false;
    }
    else
    {

         //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }

        int flags = IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if ((initted&flags) != flags) {
            printf("Failed to initialize image! %s\n", IMG_GetError());
            success = false;
        }

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

//Calculate clicks
void mouseClick()
{
    int x = mouseX;
    int y = mouseY;

    printf("MouseX: %i, MouseY: %i\n", x, y);

    Entity* ent = sc->getCurrentScene()->entities[0];
    ent->x = x;
    ent->y = y;
    ent->setScale(2);
    //ent->setRotation(0.785398);
}

bool loadMedia() {
    bool success = true;
    happy.loadTexture(renderer, "happy.png");
    happy.setSize(100,100);

    gFont = TTF_OpenFont( "ttfs/Marlboro.ttf", 28 );
    if (gFont==NULL) {
        printf("couldn't load font gfont! %s\n", TTF_GetError());
        success = false;
    }
    return success;
}


bool render()
{
    //Set clear out color!
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); // Clear our screen



    sc->getCurrentScene()->render(renderer);

    //FPS Drawing
    std::stringstream s;
    s.str("");
    s<<"FPS:"<<fps;
    SDL_Color col = {0,255,0,255};

    f.renderText(renderer, s.str().c_str(), col, gFont);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    f.render(renderer, 5, 5);

    happy.render(renderer, 100, 100);

    //Present our screen to the window!
    SDL_RenderPresent(renderer);


    return true;
}
