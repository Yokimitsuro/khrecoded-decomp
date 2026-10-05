#include "nitro/types.h"

typedef struct StageSlots {
    u8 pad_00000[0x18d78];
    void *slots[1];
} StageSlots;

extern StageSlots *data_ov001_020a0528;
extern int func_ov001_0208f1d0(void *slot, int entry);

int ReleaseStageSlotEntry(int index, int slot)
{
    return func_ov001_0208f1d0(data_ov001_020a0528->slots[index], slot);
}
