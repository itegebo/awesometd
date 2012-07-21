#include <stdio.h>

#include <SDL.h>

#include "menu.h"
#include "video.h"
#include "input.h"
#include "game.h"

struct main
{
    int last_draw;
    int f;
};

struct all
{
    struct video v;
    struct input i;
    struct game g;
    struct menu mn;

    struct main m;
};

int main(int argc, char *argv[])
{
    struct all all = {0};

    if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0 )
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    all.v = vSetup();
    all.mn = mSetup();

    while ( !iEventLoop(&all.i, &all.g, &all.mn) && all.mn.quit == 0 ) // Inputhandling is done here.
    {
        switch(all.g.state)
        {
        case GAMESTATE_INGAME:
            gDo(&all.g);
            break;
        case GAMESTATE_MENU:
            mDo(&all.mn);
            break;
        }

        // Drawing is done here.
        vDraw(&all.v, &all.g, &all.mn);

        all.m.f++;
        if ( all.i.f.debug )
            printf("Frame: %d\n", all.m.f);

        int t = (1000/FPS)-(SDL_GetTicks()-all.m.last_draw);
        if ( t > 0 && t < 1000 ) SDL_Delay(t);
        all.m.last_draw = SDL_GetTicks();
    }

    return 0;
}
