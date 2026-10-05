#include "nitro/types.h"

extern u8 *data_0205fe0c;

void ClearItemCountsByGroup(int group)
{
    u8 *itemCounts = data_0205fe0c + 0x28d8;

    switch (group) {
    case 1:
        itemCounts[0x164] = 0;
        break;
    case 2:
        itemCounts[0x168] = 0;
        itemCounts[0x169] = 0;
        itemCounts[0x16a] = 0;
        itemCounts[0x16b] = 0;
        itemCounts[0x16c] = 0;
        itemCounts[0x16d] = 0;
        itemCounts[0x16e] = 0;
        itemCounts[0x16f] = 0;
        itemCounts[0x170] = 0;
        itemCounts[0x171] = 0;
        itemCounts[0x172] = 0;
        itemCounts[0x173] = 0;
        itemCounts[0x174] = 0;
        itemCounts[0x175] = 0;
        itemCounts[0x176] = 0;
        itemCounts[0x177] = 0;
        break;
    case 5:
        itemCounts[0x188] = 0;
        break;
    case 7:
        itemCounts[0x18c] = 0;
        itemCounts[0x18d] = 0;
        itemCounts[0x18e] = 0;
        itemCounts[0x18f] = 0;
        itemCounts[0x190] = 0;
        itemCounts[0x191] = 0;
        itemCounts[0x192] = 0;
        itemCounts[0x194] = 0;
        break;
    }
}
