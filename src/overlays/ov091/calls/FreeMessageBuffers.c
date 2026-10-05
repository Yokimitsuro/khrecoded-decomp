#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u16 *messageBuffers[3];
} MenuScene;

extern void ZeroHalfThenFree(u16 *buffer);

void FreeMessageBuffers(MenuScene *scene)
{
    int i;

    for (i = 0; i < 3; i++) {
        ZeroHalfThenFree(scene->messageBuffers[i]);
    }
}
