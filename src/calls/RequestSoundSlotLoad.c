#include "nitro/types.h"

typedef struct SoundLoadSlot {
    s32 handle;
    u16 fileId;
    u8 state;
    u8 pad_07;
} SoundLoadSlot;

typedef struct SoundWork {
    u8 pad_00[0xb44c8];
    SoundLoadSlot slots[1];
} SoundWork;

extern SoundWork *data_0206084c;
extern s32 QueueTypedMessageWithHandle_0202cb38(u16 field1, u16 field2, s32 arg2);

BOOL RequestSoundSlotLoad(int index, u32 fileId)
{
    SoundLoadSlot *slot = &data_0206084c->slots[index];

    if (slot->state != 0) {
        return FALSE;
    }
    slot->state = 1;
    slot->handle = QueueTypedMessageWithHandle_0202cb38((u16)index, (u16)fileId, (s32)&slot->state);
    slot->fileId = fileId;
    return TRUE;
}
