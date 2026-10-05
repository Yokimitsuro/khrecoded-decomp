#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x8c];
    s32 field_8c;
    u8 pad_90[0x10];
    s32 field_a0;
    u8 pad_a4[0x1c];
    s32 state;
} PanelState;

extern PanelState *data_0205fe24;
extern void *NNSi_FndAllocFromDefaultHeap(int size);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void InitPanelResources(void);
extern void RegisterPanelCallbacks(void);

void InitPanelState(void) {
    PanelState *panel;

    if (data_0205fe24 == NULL) {
        panel = NNSi_FndAllocFromDefaultHeap(200);
        data_0205fe24 = panel;
        MI_CpuFill8(panel, 0, 200);
        panel->field_a0 = -8;
        panel->field_8c = -1;
        InitPanelResources();
        RegisterPanelCallbacks();
        panel->state = 3;
    }
}
