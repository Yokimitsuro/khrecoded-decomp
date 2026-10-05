#include "nitro/types.h"

typedef struct EventObject EventObject;

struct EventObject {
    u8 pad_000[0x218];
    void (*update)(EventObject *object);
};

typedef struct EventEntry {
    u8 pad_00[0x8];
    EventObject *object;
    u8 pad_0C[0x1c];
} EventEntry;

typedef struct EventContext {
    EventEntry entries[3];
    u8 pad_78[0x4];
    s32 entryCount;
} EventContext;

extern EventContext *data_ov001_020a04bc;
extern BOOL func_ov001_020645c8(u32 value);

void UpdateEventObjects(void)
{
    EventContext *context = data_ov001_020a04bc;
    EventObject *object;
    int i;

    if (context == NULL || func_ov001_020645c8(0x360c)) {
        return;
    }
    for (i = 0; i < context->entryCount; i++) {
        object = data_ov001_020a04bc->entries[i].object;
        if (object != NULL && object->update != NULL) {
            object->update(object);
        }
    }
}
