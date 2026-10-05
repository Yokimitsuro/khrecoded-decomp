#include "nitro/types.h"

extern u32 func_ov039_020bc9cc(void);
extern void func_02001620(void *layer, u32 x, u32 y, u32 color, u32 flags, int text,
                          u32 narrowFont, int maxWidth);

void DrawShadowedTextFitted(void *layer, u32 x, u32 y, u32 color, u32 flags, int text,
                                     int maxWidth)
{
    func_02001620(layer, x + 1, y + 1, color + 1, flags, text, func_ov039_020bc9cc(), maxWidth);
    func_02001620(layer, x, y, color, flags, text, func_ov039_020bc9cc(), maxWidth);
}
