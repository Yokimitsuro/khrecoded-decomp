#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 slotA;
    u32 slotB;
    u32 freeFlag;
    u8 pad_14[0x30];
    u32 registration;
    u8 pad_48[0x10];
    u8 engineObject[1];
} ScreenState;

extern void FreeSceneListObject(u32 arg0);
extern int Obj_Release(void *object);
extern int ZeroHalfThenFree(void *arg0);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern ScreenState *data_ov023_020b6f84;

void DestroyScreenState(void)
{
    ScreenState *state;

    state = data_ov023_020b6f84;
    FreeSceneListObject(state->registration);
    Obj_Release(state->engineObject);
    ZeroHalfThenFree((void *)state->slotA);
    ZeroHalfThenFree((void *)state->slotB);
    if (state->freeFlag != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)state->freeFlag);
    }
    data_ov023_020b6f84 = (ScreenState *)0;
}
