#include "nitro/types.h"

typedef struct EntryGroupDesc {
    const void *resource;
    s32 slotCount;
    s32 mode;
    BOOL fixedSlots;
    u32 reserved;
} EntryGroupDesc;

typedef struct Actor {
    u8 pad_00[0x64];
    s16 groupId;
} Actor;

extern const u8 sOv019_BaEfDbhit_020a36b0[];
void ZeroBytes0x14(void *obj);
int func_ov021_020a89c8(EntryGroupDesc *desc);

void EnsureOwnedEntryGroup(Actor *self)
{
    EntryGroupDesc desc;
    if (self->groupId == -1) {
        ZeroBytes0x14(&desc);
        desc.slotCount = 1;
        desc.mode = 1;
        desc.fixedSlots = FALSE;
        desc.resource = sOv019_BaEfDbhit_020a36b0;
        self->groupId = func_ov021_020a89c8(&desc);
    }
}
