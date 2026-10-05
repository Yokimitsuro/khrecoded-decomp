#include "nitro/types.h"

extern u16 FX_Atan2Idx(int y, int x);
extern void func_ov021_020ae8ac(u16 *node);

typedef struct Actor {
    u8 pad0[2];
    s8 slot;
    u8 pad3[0x21];
    int dirY;
    u8 pad28[4];
    int dirX;
    u16 node[0x3e];
    u16 angle;
    u8 padAe[0x154 - 0xae];
} Actor;

typedef struct Group {
    u8 pad0[8];
    Actor *actors;
    u8 padC[9];
    u8 count;
    u8 pad16[0x2a];
    s8 flags;
    u8 pad41[3];
    u16 node[1];
} Group;

void UpdateGroupAngles(Group *group)
{
    Actor *actor;
    int i;
    for (i = 0; i < group->count; i++) {
        actor = &group->actors[i];
        if (actor->slot != -1) {
            actor->angle = FX_Atan2Idx(actor->dirY, actor->dirX);
            actor->node[0] |= 0x20;
            func_ov021_020ae8ac(actor->node);
        }
    }
    if (group->flags & 1) {
        func_ov021_020ae8ac(group->node);
    }
}
