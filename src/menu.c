#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "menu.h"
#include "hiscore.h"
#include "filepath.h"

const char *levels[] =
{
    "share/level",
    NULL
};

static struct menuelement * mPopulateLevelList(void)
{
    char *p;
    struct menuelement *te = calloc('\0', sizeof(struct menuelement));
    struct menuelement *ce = te;
    struct dirent *ent;
    DIR *dir;

    dir = opendir("share/level");
    if (!dir)
    {
        printf("Error: Can't find directory with levels.!\n");
        exit(1);
    }
    closedir(dir);

    if ( !te->text )
    {
        free(te);
        return NULL;
    }
    return te;
}

struct menu mSetup(void)
{
    struct menu m;
    m.hovering = -1;
    m.quit = 0;
    m.mainmenu[0] = "new game";
    m.mainmenu[1] = "leaderboards";
    m.mainmenu[2] = "tutorial";
    m.mainmenu[3] = "visit our homepage";
    m.mainmenu[4] = "quit";
    m.levels = fpEnumerate(levels, NULL);
    m.level_p = m.level_h = 0;

    return m;
}

void mDo(struct menu *m)
{
    return;
}
