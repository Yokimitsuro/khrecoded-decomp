#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x48];
    s32 unk_4C;
} EffectParams;

typedef struct {
    u8 pad_00[2];
    s8 state;
    u8 pad_03;
    s32 timer;
    u8 pad_08[0x130];
    EffectParams *params;
    u8 pad_13C[2];
    s16 slots[8];
} EffectObj;

extern void RebindModelAnimTracks(EffectObj *obj);

void AdvanceToSecondPhase(EffectObj *obj)
{
    EffectParams *params = obj->params;
    int i;

    if (obj->state == 2) {
        return;
    }
    obj->timer = 0;
    if (params->unk_4C >= 0) {
        RebindModelAnimTracks(obj);
        if (!(params->flags & 0x400)) {
            for (i = 0; i < 8; i++) {
                obj->slots[i] = -1;
            }
        }
        obj->state = 2;
        return;
    }
    obj->state = -1;
}
