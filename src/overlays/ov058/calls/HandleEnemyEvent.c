#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x850];
    u8 blendTable[4];
} EnemyActor;

extern void ChangeActorState(EnemyActor *actor, void *blendTable, int state, int blendIndex, int frames);
extern void RequestActorMode(EnemyActor *actor, int state, int frames, int blendIndex);

void HandleEnemyEvent(EnemyActor *actor, int event, int frames)
{
    int delay = 0;
    void *blendTable = NULL;
    int blendIndex = -1;

    switch (event) {
    case 10:
        frames = 5;
        break;
    case 0xd:
        blendIndex = 0;
        blendTable = actor->blendTable;
        break;
    case 0xe:
        blendTable = actor->blendTable;
        blendIndex = 1;
        delay = 5;
        break;
    }
    if (blendTable != NULL) {
        ChangeActorState(actor, blendTable, event, blendIndex, delay);
        return;
    }
    RequestActorMode(actor, event, frames, blendIndex);
}
