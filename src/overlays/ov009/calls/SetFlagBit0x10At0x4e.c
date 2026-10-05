#include "nitro/types.h"

void SetFlagBit0x10At0x4e(int obj, BOOL enable) {
    if (enable) {
        *(u16 *)(obj + 0x4e) = *(u16 *)(obj + 0x4e) | 0x10;
        return;
    }
    *(u16 *)(obj + 0x4e) = *(u16 *)(obj + 0x4e) & 0xffef;
}
