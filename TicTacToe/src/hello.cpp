

#include <SDL.h>
#include <SDL_image.h>
#include <hello.h>
#include <cstdio>

//Boolean to check if we should quit the program (press the x button)
bool quit;

//Screen width and height set as constants!
const int screenWidth = 600;
const int screenHeight = 600;

//Button objects (3*3)=9
button buttons[9];

//Variables for the mouse positions!
int mouseX;
int mouseY;

//Player turn 1=player 1 || 2=player2
int turn = 1;

//Main function
int main( int argc, char* args[] ) {

    //Does initialization return true?
    if (init()) {

        //We don't want to quit!
        quit = false;
        //We don't have a winner yet.
        bool winner = false;

        //SDL Event Poller
        SDL_Event e;

        Uint32 countedFrames = 0;//How many frames have we counted in the last second?
        Uint8 ticksPerFrame = 1000/60;//Framerate
        Uint32 startTick = SDL_GetTicks(); //The tick we started counting frames
        Uint32 nextFrame = startTick;//The next tick that we should render the next frame
        Uint32 curTick;//The current tick we are on!

        //The tick we should restart the game!
        Uint32 nextGame = 0;

        background = loadTexture("background.png"); //3x3 grid
        xMark = loadTexture("Xmark.png"); // x tile
        oMark = loadTexture("Omark.png"); // o tile

        //Calculate the size of each tile
        int sizeX = screenWidth / 3;
        int sizeY = screenHeight / 3;

        //printf("sizex : %i\n", sizeX);

        //Initialize buttons
        int on = 0;
        for (int x = 0; x < 3; x++) {

            for (int y = 0; y < 3; y++) {
                //printf("%i\n", on);
               // *buttons[on] = new button();
                button& b = buttons[on];
                b.x = x*sizeX;
                b.y = y*sizeY;
                b.w = sizeX;
                b.h = sizeY;

                on++;
            }
        }

        //The winner number (player 1 or 2?)
        int win;

        //Main game loop
        while (!quit) {

            //Set the current tick
            curTick = SDL_GetTicks();

            //Go through all of the events since last run-through!
            while (SDL_PollEvent(&e) != 0) {
                if (e.type==SDL_QUIT) { //Did we close the game?
                    quit = true;
                } else if (!winner && e.type==SDL_MOUSEBUTTONDOWN) { //Was the mouse pressed once?
                    mouseClick();
                }
            }

            //Find the mouse position relative to the window, and set it to mouseX and mouseY.
            SDL_GetMouseState(&mouseX, &mouseY);

            //Has enough time passed to render the next frame?
            if (curTick>=nextFrame) {
                nextFrame = curTick+ticksPerFrame;
                countedFrames++;
                //Has it been a second? Print the fps!
                if (startTick+1000 < SDL_GetTicks()) {
                    printf("FPS : %i\n",countedFrames);
                    countedFrames = 0;
                    startTick = SDL_GetTicks();
                }

                render();


               // SDL_Delay(ticksPerFrame);
            }

            //Has somebody won?
            if (winner ) {

                //Should we restart yet? If so, clean up!
                if (SDL_GetTicks() > nextGame) {
                    for (int x = 0; x < 9; x++) {
                        buttons[x].who = 0;
                        turn = 1;
                    }
                    winner = false;
                }


            } else {
                //Who won the game?
                win = checkWin();
                if (win>0) {
                    if (win==1) {
                        printf("X WINS!\n");
                    } else if (win==2) {
                        printf("O WINS!\n");
                    } else {
                        printf("TIE!\n");
                    }
                    winner = true;
                    //Time we should restart!
                    nextGame = SDL_GetTicks() + 5000;//5 seconds!
                }
            }


        }

    } else {
        printf("Failed to initialize!");
    }

    //Deallocate and quit!
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(xMark);
    SDL_DestroyTexture(oMark);
    IMG_Quit();
    SDL_Quit();
    return 0;
}



bool init() {


    bool success = true;

    //Init video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize video! %s\n", SDL_GetError());
        success = false;
    } else {
        //Make window
        window = SDL_CreateWindow("Test window!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if (window==NULL) {
            printf("Could not create window! %s\n", SDL_GetError());
            success = false;
        } else {
            //Make renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer==NULL) {
                printf("Could not create renderer! %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}

//Load a texture from a string and return the created texture!
SDL_Texture* loadTexture(std::string s) {
    SDL_Surface* loadedSurface = IMG_Load(s.c_str());
    if (loadedSurface==NULL) {
        printf("Could not load image! %s\n", IMG_GetError());
        //quit = true;
    } else {

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
bool renderTexture(SDL_Renderer* r, SDL_Texture* t, int x, int y, int w, int h) {

    SDL_Rect rect = {x,y,w,h};
    SDL_RenderCopy(r, t, NULL, &rect);

    return true;
}

//Render buttons if they have who > 0
void renderButton(int t) {

    button&b = buttons[t];
    SDL_Texture* mark;
    if (b.who==1) {
        mark = xMark;
    } else if (b.who==2) {
        mark = oMark;
    }

    renderTexture(renderer, mark, b.x, b.y, b.w, b.h);

}

//Easy way to switch turns
void switchTurn() {
    if (turn==1) {
        turn = 2;
    } else if (turn==2) {
        turn = 1;
    }
}

//Calculate which tile we clicked!
void mouseClick() {

    for (int x = 0; x < 9; x++) {
        button& b = buttons[x];

        if ((b.who<1) && (mouseX > b.x) && (mouseX < b.x+b.w) && (mouseY > b.y) && (mouseY < b.y+b.h)) {
            b.who = turn;
            switchTurn();
        }
    }
}


bool render() {
    SDL_RenderClear(renderer); // Clear our screen

    //Render our background first!
    renderTexture(renderer, background, 0, 0, screenWidth, screenHeight);

    //Render our buttons if who > 0 (player has clicked it!)
    for (int x = 0; x < 9; x++) {
        button& b = buttons[x];
        if (b.who>0) {
            renderButton(x);
        }
    }

    //Present our screen to the window!
    SDL_RenderPresent(renderer);

    return true;
}

//Are these 3 buttons the same player owned?
int same(button& b1, button& b2, button& b3) {
    int t = b1.who;
    bool isSame = true;
    //Are these not owned, or are they different from each other?
    if (t == 0 || (b2.who!=b1.who || b3.who!=b1.who)) {
        isSame = false;
    }

    //If they are the same, return the player who won!
    if (isSame) {
        return t;
    }
    return 0;
}



int checkWin() {

    int w;//winner

    //Go through each possible win condition!
    w = same(buttons[0],buttons[1],buttons[2]);
    if (w>0) {
        return w;
    }

    w = same(buttons[3],buttons[4],buttons[5]);
    if (w>0) {
        return w;
    }

    w = same(buttons[6],buttons[7],buttons[8]);
    if (w>0) {
        return w;
    }

    w = same(buttons[0],buttons[3],buttons[6]);
    if (w>0) {
        return w;
    }

    w = same(buttons[1],buttons[4],buttons[7]);
    if (w>0) {
        return w;
    }

    w = same(buttons[2],buttons[5],buttons[8]);
    if (w>0) {
        return w;
    }

    w = same(buttons[0],buttons[4],buttons[8]);
    if (w>0) {
        return w;
    }

    w = same(buttons[2],buttons[4],buttons[6]);
    if (w>0) {
        return w;
    }

    //Are we tied? See if all tiles are owned. We wouldn't have gotten this far if somebody won!
    int n = 0;
    for (int x = 0; x < 9; x++) {
        if (buttons[x].who > 0) {
            n++;
        }
    }
    //tie
    if (n>=9) {
        return 3;
    }

    return 0;
}
