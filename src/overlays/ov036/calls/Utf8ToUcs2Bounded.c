#include "nitro/types.h"

extern int strlen(const char *str);

int Utf8ToUcs2Bounded(const char *src, u16 *dst, int dstCount)
{
    int len;
    int i;
    char c;
    u16 *end;
    int lastIndex = dstCount - 1;

    len = strlen(src);
    i = 0;
    if (i < len) {
        end = dst + lastIndex;
        do {
            c = src[i];
            if (c >= 1 && c < 0x20) {
                i++;
                *dst = c;
                if (c == 3) {
                    i++;
                }
            } else if (c >= 0x20 && c < 0x80) {
                *dst = c;
                i++;
            } else if ((c & 0xe0) == 0xc0) {
                *dst = ((u16)(c & 0x1f) << 6) | (u16)(src[i + 1] & 0x3f);
                i += 2;
            } else if ((c & 0xf0) == 0xe0) {
                *dst = ((u16)(c & 0xf) << 12) | ((u16)(src[i + 1] & 0x3f) << 6) | (u16)(src[i + 2] & 0x3f);
                i += 3;
            }
            dst++;
            if (dst >= end) {
                break;
            }
        } while (i < len);
    }
    *dst = 0;
    return len;
}
