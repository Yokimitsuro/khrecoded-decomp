#include "nitro/types.h"

typedef struct MenuScene {
    u8 pad_00[0x10];
    u16 *archiveFiles[2];
} MenuScene;

extern void ZeroHalfThenFree(u16 *buffer);

void FreeArchiveFiles(MenuScene *scene)
{
    int i;

    for (i = 0; i < 2; i++) {
        ZeroHalfThenFree(scene->archiveFiles[i]);
    }
}
