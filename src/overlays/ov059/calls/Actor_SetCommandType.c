#include "nitro/types.h"

typedef struct Actor {
    u8 pad_0000[0x170c];
    s32 commandTypes[1];
    u8 commandCount;
    s8 commandIndex;
} Actor;

extern void func_ov001_02078800(s32 entryId);

void Actor_SetCommandType(Actor *actor, s32 commandType)
{
    actor->commandTypes[actor->commandIndex] = commandType;
    switch (actor->commandTypes[actor->commandIndex]) {
    case 0:
        func_ov001_02078800(0xdd);
        break;
    case 1:
        func_ov001_02078800(0xde);
        break;
    case 2:
        func_ov001_02078800(0xdf);
        break;
    case 3:
        func_ov001_02078800(0xe0);
        break;
    }
}
