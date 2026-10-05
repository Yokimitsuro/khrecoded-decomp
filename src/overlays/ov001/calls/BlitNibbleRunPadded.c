#include "nitro/types.h"

void BlitNibbleRunPadded(u8 *dst, int right, int count, int width,
                                  int pad, int row, const u8 *src) {
    int total = pad + width;
    int start = ((total + 7) / 8) * 8 - (right + pad + 1);
    int i;
    u8 *p;

    if (total % 8 == 0) {
        start += 8;
    }
    if (start < 0) {
        start = 0;
    }
    p = (u8 *)((start % 8) / 2 + ((start / 8) * 0x20 + row * 4) + (int)dst);

    if ((start & 1) != 0) {
        for (i = 0; i < count; i++) {
            *p = (u8)((*p & 0xf) | (src[i] << 4));
            p += 4;
        }
        return;
    }
    for (i = 0; i < count; i++) {
        *p = (u8)((*p & 0xf0) | src[i]);
        p += 4;
    }
}
