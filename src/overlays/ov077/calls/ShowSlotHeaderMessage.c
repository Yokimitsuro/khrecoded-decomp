#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x2db4];
    u16 slotRecords[1];
} GameState;

typedef struct {
    u8 pad_00000[0x4e70];
    u8 messages[0x11ff8 - 0x4e70];
    s32 slot;
} MenuWork;

extern GameState *data_0205fe0c;
extern void *func_ov027_020ba2c8(void *messages, int index);
extern void func_ov077_020c5964(MenuWork *work, void *text);

void ShowSlotHeaderMessage(MenuWork *work)
{
    BOOL assigned = FALSE;
    int messageId;

    if (work->slot >= 2 && data_0205fe0c->slotRecords[work->slot] != 0xffff) {
        assigned = TRUE;
    }
    messageId = 0x59;
    if (!assigned) {
        messageId = 0;
    }
    func_ov077_020c5964(work, func_ov027_020ba2c8(work->messages, messageId));
}
