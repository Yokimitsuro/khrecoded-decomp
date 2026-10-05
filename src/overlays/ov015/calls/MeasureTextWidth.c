#include "nitro/types.h"

extern int func_0200191c(void *font, const u16 *text, const u16 **next);

int MeasureTextWidth(void *font, const u16 *text, int maxLines)
{
    int maxWidth = 0;
    int lines = 0;
    const u16 *next = NULL;
    int width;

    while (text != NULL) {
        width = func_0200191c(font, text, &next);
        if (maxWidth < width) {
            maxWidth = width;
        }
        lines++;
        text = next;
        if (maxLines > 0 && lines >= maxLines) {
            break;
        }
    }
    return maxWidth;
}
