#include "nitro/types.h"

typedef struct {
    u8 data[0x30];
} SpriteSlot;

typedef struct {
    u32 ids[7];
} SpriteFileIds;

typedef struct {
    u8 pad_000[0xfc];
    SpriteSlot *slots;
} SlotManager;

extern SlotManager *data_ov001_020a04bc;
extern const SpriteFileIds data_ov001_0209db2c;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern u32 MakePrimaryVramKey(u32 slot);
extern BOOL InitSlotFromFile(SpriteSlot *slot, u32 fileId);

void LoadManagerSpriteSlots(void)
{
    SlotManager *manager = data_ov001_020a04bc;
    SpriteFileIds fileIds;
    int i;

    if (manager != NULL && manager->slots == NULL) {
        manager->slots = NNSi_FndAllocFromDefaultHeap(7 * sizeof(SpriteSlot));
        fileIds = data_ov001_0209db2c;
        for (i = 0; i < 7; i++) {
            InitSlotFromFile(&manager->slots[i], MakePrimaryVramKey(fileIds.ids[i]));
        }
    }
}
