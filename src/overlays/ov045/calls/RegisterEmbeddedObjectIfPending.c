#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    u32 pending;
    u8 pad_20[0x34 - 0x20];
    u32 ready;
    u8 pad_38[0x19bc - 0x38];
    u8 embedded[1];
} Ov045EmbeddedState;

extern Ov045EmbeddedState *data_ov045_020c08a0;

extern void FlushBufferAndRunCallback(void *object);

/* Registers a pending embedded object and marks it ready. */
void RegisterEmbeddedObjectIfPending(void)
{
    if (data_ov045_020c08a0->pending != 0) {
        FlushBufferAndRunCallback(data_ov045_020c08a0->embedded);
        data_ov045_020c08a0->ready = 1;
    }
}
