#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u8 enabled : 1;
    u8 pad_11[0x18 - 0x11];
    int frame;
    u8 pad_1c[0xc4 - 0x1c];
} AnimEntry;

typedef struct {
    u8 pad_00[0xc4];
    AnimEntry *entries;
} FieldOwner;

typedef struct {
    u8 pad_00[4];
    FieldOwner *owner;
    u8 pad_08[0x32 - 0x08];
    u8 actorId;
    u8 animIndex;
    u8 pad_34[0xbe - 0x34];
    u8 unk_BE_low : 4;
    u8 state : 4;
    u8 pad_bf;
    u32 flags;
} FieldObject;

typedef struct {
    u8 pad_00[4];
    u8 node[4];
} Actor;

extern BOOL func_ov001_020872e0(FieldObject *obj);
extern void func_ov016_020a2688(FieldObject *obj, int enabled);
extern Actor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void RebindAnimTracks(void *node, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *node);

void SyncFieldObjectAnimation(FieldObject *obj)
{
    AnimEntry *entry = obj->owner->entries;
    Actor *actor;
    int enabled;

    if (entry == NULL) {
        return;
    }
    entry = &entry[obj->animIndex];
    if (!entry->enabled) {
        return;
    }
    enabled = obj->flags & 1;
    if (!func_ov001_020872e0(obj)) {
        enabled = 0;
    }
    if (obj->state == 6) {
        return;
    }
    func_ov016_020a2688(obj, enabled);
    if (obj->flags & 0x20) {
        actor = ActorRegistry_GetEntityByIndex(obj->actorId);
        RebindAnimTracks(actor->node, 1, entry->frame);
        Flags16_ClearBit1(actor->node);
    }
}
