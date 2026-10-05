#include "nitro/types.h"

typedef struct Entity {
    u8 pad_000[0x75c];
    int currentState;
    u8 pad_760[0x774 - 0x760];
    u8 blendTable[4];
} Entity;

extern void func_ov052_020ce0e0(Entity *entity, void *blendTable, int state, int blendIndex, int frames);
extern void func_ov052_020cde40(Entity *entity, int state, int frames);

void RequestOverlay054ActorState(Entity *entity, int state, int frames)
{
    int blendIndex = -1;

    switch (state) {
    case 0:
        blendIndex = 0;
        break;
    case 1:
        blendIndex = 1;
        break;
    case 2:
        blendIndex = 2;
        break;
    case 10:
        blendIndex = 3;
        break;
    case 3:
        blendIndex = 4;
        break;
    case 4:
        blendIndex = 5;
        break;
    case 5:
        blendIndex = 6;
        break;
    case 0x1e:
        blendIndex = 11;
        break;
    case 6:
        blendIndex = 7;
        break;
    case 7:
        blendIndex = 8;
        break;
    case 8:
        blendIndex = 9;
        break;
    case 9:
        blendIndex = 10;
        break;
    case 0x15:
        blendIndex = 12;
        break;
    case 0x16:
        blendIndex = 13;
        frames = 5;
        break;
    }
    if (blendIndex != -1) {
        if (state == entity->currentState) {
            return;
        }
        func_ov052_020ce0e0(entity, entity->blendTable, state, blendIndex, frames);
        return;
    }
    func_ov052_020cde40(entity, state, frames);
}
