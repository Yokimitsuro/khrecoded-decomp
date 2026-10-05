#include "nitro/types.h"

extern u32 *SlotTable_GetEntry(u32 *list, u32 index);

/* Marks an indexed slot as in use. */
void ClaimSlot(u32 *list, u32 index)
{
    u32 *slot;

    slot = SlotTable_GetEntry(list, index);
    if (slot != 0) {
        *slot = 1;
    }
}
