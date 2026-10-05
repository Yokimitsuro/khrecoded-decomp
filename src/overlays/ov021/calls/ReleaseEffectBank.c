#include "nitro/types.h"

typedef struct BufferPair {
    void *primary[4];
    void *secondary[4];
} BufferPair;

typedef struct EffectBank {
    u8 pad0[4];
    u8 id;
    u8 pad5[7];
    BufferPair buffers[2];
    u8 *effects;
    int effectCount;
    u8 slots[0xc];
} EffectBank;

extern void FreeSlotTable(void *table);
extern void FreeResourceAt0x44(void *effect, int id);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ReleaseEffectBank(EffectBank *bank)
{
    int i;
    int j;

    FreeSlotTable(bank->slots);
    if (bank->effects != NULL) {
        for (i = 0; i < bank->effectCount; i++) {
            FreeResourceAt0x44(bank->effects + i * 0x90, bank->id);
        }
        NNSi_FndFreeFromDefaultHeap(bank->effects);
    }
    for (i = 0; i < 2; i++) {
        BufferPair *pair = &bank->buffers[i];
        for (j = 0; j < 2; j++) {
            if (pair->primary[j] != NULL) {
                NNSi_FndFreeFromDefaultHeap(pair->primary[j]);
            }
            if (pair->secondary[j] != NULL) {
                NNSi_FndFreeFromDefaultHeap(pair->secondary[j]);
            }
        }
    }
}
