#include "nitro/types.h"

extern int func_0200191c(int context, int value, int *remaining);
extern void Obj_SetField14(int *context, u32 value);
extern void DrawTextAnchored(int *context, u32 x, u32 y, u32 color, u32 flags, u32 value);

void func_02001620(int *context, u32 x, u32 y, u32 color, u32 flags, int value,
                    u32 overrideValue, int maxWidth)
{
    int remaining;
    int width;
    int maxSeen;
    u32 savedField;

    remaining = value;
    savedField = *context;
    maxSeen = 0;
    do {
        width = func_0200191c(context, remaining, &remaining);
        if (maxSeen < width) {
            maxSeen = width;
        }
    } while (remaining != 0);
    if (maxSeen > maxWidth) {
        Obj_SetField14(context, overrideValue);
    }
    DrawTextAnchored(context, x, y, color, flags, value);
    Obj_SetField14(context, savedField);
}
