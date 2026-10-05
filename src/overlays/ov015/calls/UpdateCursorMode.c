#include "nitro/types.h"

typedef struct CursorState {
    u8 pad_00[0x18];
    u32 flags;
    u8 pad_1c[0x54 - 0x1c];
    s8 mode;
} CursorState;

extern CursorState *data_ov015_020812e0;
extern int MarkPairedPanelSlots(void);
extern int MarkLowPanelSlots(void);
extern int MarkGroupPanelSlots(void);

int UpdateCursorMode(void)
{
    int result = 0;
    CursorState *cursor = data_ov015_020812e0;

    if (!(cursor->flags & 1)) {
        if (cursor->mode == 4) {
            result = MarkPairedPanelSlots();
        } else if (cursor->mode == 3) {
            result = MarkLowPanelSlots();
        } else {
            result = MarkGroupPanelSlots();
        }
        if (result != 0) {
            data_ov015_020812e0->flags |= 1;
        }
    }
    return result;
}
