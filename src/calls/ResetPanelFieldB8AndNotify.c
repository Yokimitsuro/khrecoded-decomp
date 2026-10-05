#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xb8];
    s32 field_b8;
} PanelState;

extern PanelState *data_0205fe24;
extern void InvokeCallbackSlot(int mode);

void ResetPanelFieldB8AndNotify(void)
{
    data_0205fe24->field_b8 = 0;
    InvokeCallbackSlot(2);
}
