#include "nitro/types.h"

typedef struct EventObject EventObject;

struct EventObject {
    u8 pad_000[0x1e8];
    void (*flaggedUpdate)(EventObject *object);
};

typedef struct EventEntry {
    u32 unk_00;
    EventObject *object;
    u8 pad_08[0x1c];
    u16 flags;
    u8 pad_26[0x2];
} EventEntry;

typedef struct EventContext {
    u32 unk_00;
    EventEntry entries[3];
    s32 entryCount;
    u8 pad_80[0xc];
    void *unk_8C;
} EventContext;

extern EventContext *data_ov001_020a04bc;

void RunFlaggedEventCallbacks(void)
{
    EventContext *context = data_ov001_020a04bc;
    EventEntry *entry;
    EventObject *object;
    int i;

    if (context == NULL || context->unk_8C == NULL) {
        return;
    }
    for (i = 0; i < context->entryCount; i++) {
        entry = &data_ov001_020a04bc->entries[i];
        if ((entry->flags & 2) > 0) {
            object = entry->object;
            if (object != NULL && object->flaggedUpdate != NULL) {
                object->flaggedUpdate(object);
            }
        }
    }
}
