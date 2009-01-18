#include <SDL.h>

#include "gfx_charmap.h"
#include "render.h"

static int charmap_inited = 0;
static const int numcharmap[256] = {
    ['0'] = 1,
    ['1'] = 2,
    ['2'] = 3,
    ['3'] = 4,
    ['4'] = 5,
    ['5'] = 6,
    ['6'] = 7,
    ['7'] = 8,
    ['8'] = 9,
    ['9'] = 10,
    ['a'] = 11,
    ['b'] = 12,
    ['c'] = 13,
    ['d'] = 14,
    ['e'] = 15,
    ['f'] = 16,
    ['g'] = 17,
    ['h'] = 18,
    ['i'] = 19,
    ['j'] = 20,
    ['k'] = 21,
    ['l'] = 22,
    ['m'] = 23,
    ['n'] = 24,
    ['o'] = 25,
    ['p'] = 26,
    ['q'] = 27,
    ['r'] = 28,
    ['s'] = 29,
    ['t'] = 30,
    ['u'] = 31,
    ['v'] = 32,
    ['w'] = 33,
    ['x'] = 34,
    ['y'] = 35,
    ['z'] = 36
};

static const int charmap[CHAR_COUNT][CHAR_SIZE_Y][CHAR_SIZE_X] = {
    {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 1, 1, 1, 0, 0, 0 },
        { 0, 1, 0, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0 },
        { 0, 1, 1, 1, 1, 0, 0, 0 },
        { 1, 1, 1, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0 },
        { 0, 1, 1, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 1, 1, 1, 1, 0, 0 },
        { 0, 1, 1, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 1, 1, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 1, 1, 1, 0, 0, 0 },
        { 0, 1, 1, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 1, 1, 1, 1, 0, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 0, 0, 0 },
        { 1, 1, 0, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 1, 1, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 0, 0 },
        { 1, 1, 0, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 0, 1, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 1, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 1, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 1, 1, 0, 0 },
        { 0, 1, 1, 1, 1, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 1, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 0, 0, 0 },
        { 1, 1, 0, 1, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 0, 0, 0 },
        { 1, 1, 0, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 0, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 0, 1, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 1, 0, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 0, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 1, 0, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    },
    {
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 0, 0, 0 },
        { 0, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    }
};

SDL_Rect charmapslices[] = {
    { 0,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 8,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 16,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 24,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 32,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 40,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 48,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 56,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 64,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 72,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 80,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 88,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 96,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 104,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 112,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 120,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 128,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 136,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 144,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 152,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 160,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 168,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 176,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 184,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 192,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 200,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 208,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 216,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 224,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 232,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 240,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 248,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 256,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 264,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 272,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 280,0,CHAR_SIZE_X,CHAR_SIZE_Y },
    { 288,0,CHAR_SIZE_X,CHAR_SIZE_Y }
};

static SDL_Surface *charmapsurface;

void init_gfx_charmap(void) {
    int i, x, y;
    Uint32 color;
    SDL_Rect pixel = { 0, 0, 1, 1 };
    charmapsurface = SDL_CreateRGBSurface(SDL_HWSURFACE, CHAR_SIZE_X*CHAR_COUNT, CHAR_SIZE_Y, 32, RMASK, GMASK, BMASK, AMASK);
    color = SDL_MapRGB(charmapsurface->format, 255,255,255);
    for (i=0;i<CHAR_COUNT;i++) {
        for (x=0;x<8;x++) {
            for (y=0;y<8;y++) {
                if ( charmap[i][y][x] == 1 ) {
                    pixel.x = x+(i*8);
                    pixel.y = y;
                    SDL_FillRect(charmapsurface,&pixel,color);
                }
            }
        }
    }
    charmap_inited++;
}

void draw_text(SDL_Surface *s, char *text, int x, int y) {
    SDL_Rect dstrect = { 0,0,CHAR_SIZE_X,CHAR_SIZE_Y };
    int i = 0;
    if ( charmap_inited == 0 ) init_gfx_charmap();
    while ( text[i] != 0 ) {
        dstrect.x = x+(i*8);
        dstrect.y = y;
        updaterect((x+(i*8))/32, y/32);
        SDL_BlitSurface(charmapsurface, &charmapslices[numcharmap[text[i]]], s, &dstrect);
        i++;
    }
}
