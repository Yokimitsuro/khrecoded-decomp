#include "nitro/types.h"

extern void DrawTextColored(void *context, int x, int y, int color, int flags, const u16 *text);

void DrawTextPackedColor(void *context, int x, int y, int color, int flags, int highColor, const u16 *text)
{
    DrawTextColored(context, x, y, color | (highColor << 8), flags, text);
}
