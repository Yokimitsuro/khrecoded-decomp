#include "nitro/types.h"

typedef struct Actor {
    u8 pad_0000[0x170c];
    s32 commandTypes[1];
    u8 commandCount;
    s8 commandIndex;
} Actor;

extern s32 func_ov001_02078494(void);
extern void func_ov001_02078000(s32 deckMode, s32 commandType);
extern BOOL func_ov001_02077ef4(void);

void Actor_ConsumeCommand(Actor *actor)
{
    s32 commandType = actor->commandTypes[actor->commandIndex];
    s32 deckMode = func_ov001_02078494();

    func_ov001_02078000(deckMode, commandType);
    func_ov001_02077ef4();
}
