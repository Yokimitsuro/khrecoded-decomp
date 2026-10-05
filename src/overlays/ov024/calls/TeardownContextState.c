#include "nitro/types.h"

extern u32 data_ov024_020b7540;
extern BOOL DestroyFndObjectList(int container);
extern void FreeResourceBufferAndProbeHeap(u32 target);
extern void FreePointerIfSet(u32 target);

void TeardownContextState(void) {
    DestroyFndObjectList(data_ov024_020b7540 + 0x6524);
    if (*(int *)(data_ov024_020b7540 + 0x66e0) != 0) {
        FreeResourceBufferAndProbeHeap(data_ov024_020b7540 + 0x650c);
        FreeResourceBufferAndProbeHeap(data_ov024_020b7540 + 0x6518);
    }
    FreePointerIfSet(data_ov024_020b7540 + 0x6500);
}
