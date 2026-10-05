#include "nitro/types.h"

extern u32 *SlotTable_GetEntry(u32 *list, u32 index);

/* Marks an indexed slot as free. */
void ReleaseSlot(u32 *list, u32 index)
{
    u32 *slot;

    slot = SlotTable_GetEntry(list, index);
    if (slot != 0) {
        *slot = 0;
    }
}
