#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc];
    void *bufferC;
    void *buffer10;
    u8 pad_14[0x64 - 0x14];
    void *buffer64;
} PanelState;

extern PanelState *data_0205fe24;
extern void setDualArrayEntry(int page, int a, int b);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ShutdownPanelState(void) {
    PanelState *panel = data_0205fe24;

    if (panel != NULL) {
        setDualArrayEntry(0, 0, 0);
        setDualArrayEntry(1, 0, 0);
        setDualArrayEntry(2, 0, 0);
        NNSi_FndFreeFromDefaultHeap(panel->buffer64);
        NNSi_FndFreeFromDefaultHeap(panel->buffer10);
        NNSi_FndFreeFromDefaultHeap(panel->bufferC);
        NNSi_FndFreeFromDefaultHeap(panel);
        data_0205fe24 = NULL;
    }
}
