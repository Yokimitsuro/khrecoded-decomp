#include "nitro/types.h"

typedef struct {
    u8 data[0x2c];
} BlendTable;

typedef struct {
    int id;
    int category;
    u8 pad_08[0xc];
    int level;
} Reaction;

typedef struct {
    u8 pad_0000[0x75c];
    int mode;
    u8 pad_0760[0x774 - 0x760];
    BlendTable baseTable;
    BlendTable moveTable;
    BlendTable attackTable;
    BlendTable guardTable;
    BlendTable jumpTable;
    u8 pad_0850[0x9ac - 0x850];
    u64 stateFlags;
    u8 pad_09b4[0xa51 - 0x9b4];
    s8 formLevel;
    u8 pad_0a52[0x101c - 0xa52];
    u8 slots[0x1070 - 0x101c];
    u8 members[0x1078 - 0x1070];
    Reaction *reaction;
} Actor;

extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void *func_ov040_020be028(int index);
extern void *InvokeMemberHandler(void *list, int index, int arg);
extern void *FindSlotRecordById(void *table, int id, int *outIndex);
extern void ChangeActorState(Actor *actor, void *blendTable, int state, int blendIndex, int frames);

void RequestActorMode(Actor *actor, int state, int frames)
{
    int index;
    void *table = NULL;
    Reaction *reaction;

    if (actor->mode == state) {
        return;
    }
    if (state < 0xb) {
        table = &actor->baseTable;
        index = state;
    } else if (state >= 0xb && state < 0xd) {
        table = &actor->moveTable;
        index = state - 0xb;
    } else if (state >= 0xd && state < 0x15) {
        table = &actor->attackTable;
        index = state - 0xd;
    } else if (state >= 0x15 && state < 0x17) {
        table = &actor->guardTable;
        index = state - 0x15;
    } else if (state >= 0x17 && state < 0x1a) {
        table = &actor->jumpTable;
        index = state - 0x17;
    } else if ((state >= 0x1e && state < 0x2c) || (state >= 0x43 && state < 0x5f)) {
        int handlerArg = 0;
        index = 0;
        reaction = actor->reaction;
        if (reaction == NULL) {
            if (func_ov001_02063a38() == 6) {
                if (!(actor->stateFlags & 0x40) || func_ov001_020645c8(0x3520)) {
                    handlerArg = 1;
                }
                table = func_ov040_020be028(handlerArg);
            }
        } else {
            switch (reaction->category) {
            case 1:
                if (!(actor->stateFlags & 0x40) || func_ov001_020645c8(0x3520)) {
                    handlerArg = reaction->level - 1;
                }
                break;
            case 2:
                if (state == 0x20) {
                    handlerArg = 1;
                }
                break;
            case 3:
                handlerArg = actor->formLevel;
                break;
            case 4:
                if (reaction->id == 0xc6) {
                    handlerArg = actor->formLevel;
                }
                break;
            default:
                handlerArg = 0;
                break;
            }
            table = InvokeMemberHandler(actor->members, -1, handlerArg);
        }
    } else if (state >= 0x2d && state < 0x43) {
        index = 0;
        table = FindSlotRecordById(actor->slots, state - 0x2d, NULL);
    }
    ChangeActorState(actor, table, state, index, frames);
}
