#include "button.h"

button::button()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    who = 0;
}

button::button(int x, int y, int w, int h)
{
    x = x;
    y = y;
    w = w;
    h = h;
    who = 0;
}

button::~button()
{

}

