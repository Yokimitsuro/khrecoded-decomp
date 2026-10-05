#include "nitro/types.h"

extern void UnregisterChannelEntry(u32 a, u32 b, int index);

void NotifyBothOrOne(u32 a, u32 b, int index) {
    int i;

    if (index < 0) {
        i = 0;
        do {
            UnregisterChannelEntry(a, b, i);
            i = i + 1;
        } while (i < 2);
        return;
    }
    UnregisterChannelEntry(a, b, index);
}
