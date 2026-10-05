#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_020a8a64(void *arg);
extern void FreeResourceBufferAndProbeHeap(void *arg);
extern void func_020257f8(void *arg);
extern void StoreGlobalArrayEntry(s32 index, s32 value);
extern s32 data_ov022_020b7c00;
extern void *data_ov022_020b7da0;
extern void CreateManagerObjects(void);

void InitMovieOverlayState(void)
{
    u8 *state = (u8 *)NNSi_FndGetCurrentRootHeap();

    func_ov022_020a8a64(state + 0x830);
    FreeResourceBufferAndProbeHeap(state + 0x824);
    func_020257f8(state + 4);
    StoreGlobalArrayEntry(3, 0);
    data_ov022_020b7c00 = -1;
    data_ov022_020b7da0 = 0;
    CreateManagerObjects();
}
