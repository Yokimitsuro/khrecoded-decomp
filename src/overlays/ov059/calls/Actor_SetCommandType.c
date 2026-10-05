#include "nitro/types.h"

typedef struct Actor {
    u8 pad_0000[0x170c];
    s32 commandTypes[1];
    u8 commandCount;
    s8 commandIndex;
} Actor;

extern void FieldMenu_FocusEntryById(s32 entryId);

void Actor_SetCommandType(Actor *actor, s32 commandType)
{
    actor->commandTypes[actor->commandIndex] = commandType;
    switch (actor->commandTypes[actor->commandIndex]) {
    case 0:
        FieldMenu_FocusEntryById(0xdd);
        break;
    case 1:
        FieldMenu_FocusEntryById(0xde);
        break;
    case 2:
        FieldMenu_FocusEntryById(0xdf);
        break;
    case 3:
        FieldMenu_FocusEntryById(0xe0);
        break;
    }
}
