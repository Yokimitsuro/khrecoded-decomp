#include "nitro/types.h"

typedef struct ActorEntry {
    u8 pad_00[8];
    u16 flags;
    u8 modelExtra;
    u8 registryTag;
    u8 pad_0C[4];
    u8 object[4];
} ActorEntry;

typedef struct ActorRegistry {
    u8 pad_000[0xc2c];
    u8 currentTag;
} ActorRegistry;

extern void func_020357ec(int slot, ActorEntry *entry, u16 group, const u8 *attributes, const void *shape, BOOL flag20, s8 priority);
extern BOOL Obj_SetModel(void *object, s32 resource, s32 source, u32 extra);
extern ActorRegistry *gActorRegistry;

BOOL ActorEntry_SetModel(ActorEntry *entry, s32 resource, s32 source, u32 extra)
{
    if ((entry->flags & 1) == 0) {
        func_020357ec(0xffff, entry, 0, NULL, NULL, TRUE, 0x20);
    }
    if (Obj_SetModel(entry->object, resource, source, extra)) {
        entry->registryTag = gActorRegistry->currentTag;
        entry->flags |= 4;
        entry->modelExtra = extra;
        return TRUE;
    }
    return FALSE;
}
