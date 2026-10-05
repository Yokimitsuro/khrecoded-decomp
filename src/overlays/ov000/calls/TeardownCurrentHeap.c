#include "nitro/types.h"

typedef struct {
    u32 slotA;
    u32 slotB;
    u8 pad_08[0x6000 + 0x68c - 8];
    u32 slotC;
} Heap;

extern Heap *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02061818(Heap *heap);
extern void ZeroHalfThenFree(u32 value);
extern u16 GetLanguageIndex(void);
extern void WriteGlobalPackedBits(int opcode, int channel, u16 value);
extern void SetCardThreadStartTick(void);

void TeardownCurrentHeap(void)
{
    Heap *heap = NNSi_FndGetCurrentRootHeap();
    u16 value;

    func_ov000_02061818(heap);
    ZeroHalfThenFree(heap->slotA);
    ZeroHalfThenFree(heap->slotB);
    ZeroHalfThenFree(heap->slotC);
    value = GetLanguageIndex();
    WriteGlobalPackedBits(0x1a02, 3, value);
    SetCardThreadStartTick();
}
