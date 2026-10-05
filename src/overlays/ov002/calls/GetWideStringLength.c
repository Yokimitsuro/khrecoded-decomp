#include "nitro/types.h"

int GetWideStringLength(const u16 *text)
{
    int length = 0;
    for (;;) {
        if (text[length] == 0) {
            break;
        }
        length++;
    }
    return length;
}
