#include "nitro/types.h"

int CountTextLines(const u16 *text)
{
    int i;
    int lines;
    u16 ch;

    lines = 0;
    i = 0;

    while (1) {
        ch = text[i];
        if (ch == 0) {
            break;
        }
        if (ch == '\n') {
            lines++;
        }
        i++;
    }
    return lines + 1;
}
