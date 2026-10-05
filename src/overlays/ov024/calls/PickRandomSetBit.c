#include "nitro/types.h"

extern u32 func_0202a9e4(u32 range);

int PickRandomSetBit(u32 mask) {
    int bit;
    int setCount = 0;
    int seenCount = 0;
    u32 choice = 0;
    int result = -1;

    for (bit = 0; bit < 32; bit++) {
        if ((1 << bit) & mask) {
            setCount++;
        }
    }
    if (setCount > 0) {
        choice = func_0202a9e4((u16)setCount);
    }
    for (bit = 0; bit < 32; bit++) {
        if ((1 << bit) & mask) {
            if (choice == seenCount) {
                result = bit;
                break;
            }
            seenCount++;
        }
    }
    return result;
}
