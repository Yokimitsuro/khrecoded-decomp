#include "nitro/types.h"

extern int strlen(const char *str);

int Utf8ToUcs2(const char *src, u16 *dst, int maxChars)
{
    int len;
    int i;
    int count;
    char c;

    len = strlen(src);
    for (i = 0, count = 0; i < len && count < maxChars - 1; count++) {
        c = src[i];
        if (c >= 1 && c < 0x20) {
            *dst = c;
            i++;
        } else if (c >= 0x20 && c < 0x80) {
            *dst = c;
            i++;
        } else if ((c & 0xe0) == 0xc0) {
            *dst = ((u16)(c & 0x1f) << 6) | (src[i + 1] & 0x3f);
            i += 2;
        } else if ((c & 0xf0) == 0xe0) {
            *dst = ((u16)(c & 0xf) << 12) | ((u16)(src[i + 1] & 0x3f) << 6) | (u16)(src[i + 2] & 0x3f);
            i += 3;
        }
        dst++;
    }
    *dst = 0;
    return len;
}
