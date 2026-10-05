#include "nitro/types.h"

typedef struct Ov082State {
    u8 pad_0000[0x36d4];
    u8 objectList[0x38];
    void *bufferA;
    void *bufferB;
} Ov082State;

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *func_ov039_020bc1c4(void);
extern void func_ov027_020b833c(void *manager);
extern void *func_ov039_020bc1ec(void);
extern void DestroyAllContainerElements(void *container);
extern void ReleaseIfMarked(void *container);
extern void DestroyFndObjectList(void *list);

void ShutdownOv082Screen(Ov082State *state)
{
    NNSi_FndFreeFromDefaultHeap(state->bufferA);
    NNSi_FndFreeFromDefaultHeap(state->bufferB);
    func_ov027_020b833c(func_ov039_020bc1c4());
    DestroyAllContainerElements(func_ov039_020bc1ec());
    ReleaseIfMarked(func_ov039_020bc1ec());
    DestroyFndObjectList(state->objectList);
    *(vu32 *)0x04001014 = 0;
    *(vu32 *)0x04001018 = 0;
    *(vu32 *)0x0400101c = 0;
    *(vu32 *)0x04001000 &= ~0xe000;
}
