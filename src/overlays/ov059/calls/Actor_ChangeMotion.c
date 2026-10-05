#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x75c];
    s32 motion;
    u8 pad_760[4];
    void *extraTable;
    u8 pad_768[0x774 - 0x768];
    u8 baseTable[0x2c];
    u8 midTable[4];
} Actor;

extern void func_ov059_020cc970(Actor *actor, void *table, int motion, int index, int arg);

void Actor_ChangeMotion(Actor *actor, int motion, int arg)
{
    void *table = NULL;
    int index;

    if (actor->motion == motion) {
        return;
    }
    if (motion < 13) {
        table = actor->baseTable;
        index = motion;
    } else if (motion >= 13 && motion < 18) {
        table = actor->midTable;
        index = motion - 13;
    } else if (motion >= 18) {
        table = actor->extraTable;
        index = motion - 18;
    }
    func_ov059_020cc970(actor, table, motion, index, arg);
}
