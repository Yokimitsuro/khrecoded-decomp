#include "nitro/types.h"

extern u16 RemapCharHighByte(u16 code);

int UnpackWideChars12(const u8 *packed, int length, u16 *out, int outSize)
{
    int i = 0;
    int written = 0;

    for (; i < length; i += 3) {
        if (written + 1 >= outSize) {
            break;
        }
        out[written] = packed[i] | ((u16)(packed[i + 2] & 0xf0) << 4);
        out[written + 1] = packed[i + 1] | ((u16)(packed[i + 2] & 0xf) << 8);
        out[written] = RemapCharHighByte(out[written]);
        out[written + 1] = RemapCharHighByte(out[written + 1]);
        written += 2;
    }
    return written;
}
