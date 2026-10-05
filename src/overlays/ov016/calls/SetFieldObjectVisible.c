#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x70 - 0x33];
    u16 drawFlags;
    u8 pad_72[0xbe - 0x72];
    u8 unk_BE_low : 4;
    u8 state : 4;
    u8 pad_bf;
    u32 flags;
} FieldObject;

extern void CacheEntry_SetActive(FieldObject *obj, int active);
extern void func_ov016_020a229c(FieldObject *obj, int visible);
extern int ActorSlot_GetByIndex(u32 actorId);
extern void ActorSlot_SetFlag8ByIndex(u32 actorId, int set);

void SetFieldObjectVisible(FieldObject *obj, int visible)
{
    if (obj->state == 6 && visible) {
        CacheEntry_SetActive(obj, 0);
        return;
    }
    if (!visible) {
        obj->flags |= 0x10;
        func_ov016_020a229c(obj, 0);
    } else {
        obj->flags &= ~0x10;
        func_ov016_020a229c(obj, 1);
        obj->drawFlags |= 0x20;
    }
    if (ActorSlot_GetByIndex(obj->actorId)) {
        ActorSlot_SetFlag8ByIndex(obj->actorId, visible);
    }
}
