#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    u16 *messageBuffers[3];
} MenuScene;

extern void ZeroHalfThenFree(u16 *buffer);

void FreeMessageBuffers_020bf70c(MenuScene *scene)
{
    int i;

    for (i = 0; i < 3; i++) {
        ZeroHalfThenFree(scene->messageBuffers[i]);
    }
}
