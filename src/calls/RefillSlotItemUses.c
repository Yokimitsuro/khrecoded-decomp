#include "nitro/types.h"

typedef struct SaveData
{
    u8 pad_0000[0x28d8];
    u8 itemCounts[0x390];
    u8 extraSlotCount;
    u8 pad_2C69[0x11B];
    u16 slotHandles[30];
    u32 slotUses[15];
} SaveData;

typedef struct CachedSlot
{
    int state;
    u32 value;
    u16 entry[2];
} CachedSlot;

typedef struct CachedSlotPair
{
    CachedSlot first;
    CachedSlot second;
} CachedSlotPair;

extern SaveData *data_0205fe0c;
extern CachedSlotPair data_0205ffc8[];

u16 RefillSlotItemUses(int index)
{
    int byteOffset = index * 4;
    CachedSlot *slot = &data_0205ffc8[index].first;
    u32 *uses = (u32 *)((u8 *)data_0205fe0c->slotUses + byteOffset);

    if (slot->state == 3 && *uses < slot->value)
    {
        u16 *handles = data_0205fe0c->slotHandles;
        u16 handle = *(u16 *)((u8 *)handles + byteOffset);
        int i = data_0205fe0c->extraSlotCount + 2;
        int remaining = (u16)(slot->value - *uses);
        s16 available = data_0205fe0c->itemCounts[handle];

        do
        {
            if (handle == handles[i * 2])
            {
                available -= (s16)data_0205fe0c->slotUses[i];
            }
        } while (--i >= 0);
        if (remaining >= available)
        {
            remaining = available;
        }
        {
            u16 amount = remaining;

            *uses += amount;
            return amount;
        }
    }
    return 0;
}
