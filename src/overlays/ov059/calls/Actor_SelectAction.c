#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0x75c];
    int currentAction;
    u8 pad_760[0x764 - 0x760];
    void *animationTable;
    u8 pad_768[0x7cc - 0x768];
    u8 actionTable[0x928 - 0x7cc];
    u64 flags;
} Actor;

extern BOOL func_ov001_020645c8(int id);
extern void func_ov059_020cc970(Actor *actor, void *table, int action, int slot, int arg);
extern void func_ov059_020cc834(Actor *actor, int action, int arg);

void Actor_SelectAction(Actor *actor, int action, int arg)
{
    void *table = actor->actionTable;
    int slot;

    if ((actor->flags & 0x40) == 0 || func_ov001_020645c8(0x3520)) {
        slot = -1;
        switch (action) {
        case 0: slot = 0; break;
        case 1: slot = 1; break;
        case 2: slot = 2; break;
        case 3: slot = 3; break;
        case 4: slot = 4; break;
        case 5: slot = 5; break;
        case 6: slot = 6; break;
        case 7: slot = 7; break;
        case 8: slot = 8; break;
        case 10: slot = 9; break;
        }
        if (slot != -1) {
            if (action == actor->currentAction) {
                return;
            }
            func_ov059_020cc970(actor, table, action, slot, arg);
            return;
        }
    } else if (table == actor->animationTable) {
        actor->currentAction = -1;
    }
    func_ov059_020cc834(actor, action, arg);
}
