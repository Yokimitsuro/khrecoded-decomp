#include "nitro/types.h"

int CountActiveSlots(u32 entity) {
    int index = 0;
    do {
        if (*(s32 *)(entity + index * 4 + 0x70) == 0) {
            break;
        }
        index = index + 1;
    } while (index < 3);
    return index + 1;
}
