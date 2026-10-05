#include "nitro/types.h"

typedef struct StageSlots {
    u8 pad_00000[0x18d78];
    void *slots[1];
} StageSlots;

extern StageSlots *data_ov001_020a0528;
extern int AllocPoolNode(void *slot);

int ReleaseStageSlot(int index)
{
    return AllocPoolNode(data_ov001_020a0528->slots[index]);
}
