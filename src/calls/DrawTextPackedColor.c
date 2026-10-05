#include "nitro/types.h"

extern void func_0200167c(void *context, int x, int y, int color, int flags, const u16 *text);

void DrawTextPackedColor(void *context, int x, int y, int color, int flags, int highColor, const u16 *text)
{
    func_0200167c(context, x, y, color | (highColor << 8), flags, text);
}
