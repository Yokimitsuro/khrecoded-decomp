#include "nitro/types.h"

void ClearBuffer5100(u8 *buffer) {
    int i;

    i = 0;
    do {
        buffer[i] = 0;
        i = i + 1;
    } while (i < 0x5100);
}
