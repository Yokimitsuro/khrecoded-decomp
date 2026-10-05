#include "nitro/types.h"

extern u8 *data_0205fe0c;

int FindSlotByActiveOrder(int targetOrder)
{
    int result;
    int index;
    int activeCount;

    result = -1;
    index = 0;
    activeCount = 0;

    do {
        if (*(u16 *)(data_0205fe0c + index * 4 + 0x2d84) != (u16)result) {
            if (activeCount == targetOrder) {
                result = index;
                break;
            }
            activeCount++;
        }
        index++;
    } while (index < 8);

    return result;
}
