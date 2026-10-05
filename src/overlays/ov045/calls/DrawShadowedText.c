#include "nitro/types.h"

typedef struct TextLayer TextLayer;

extern void DrawTextAnchored(TextLayer *obj, int x, int y, int color, u32 flags, const u16 *text);

void DrawShadowedText(TextLayer *layer, int x, int y, const u16 *text, u8 color)
{
    DrawTextAnchored(layer, x + 1, y + 1, color - 1, 0x20, text);
    DrawTextAnchored(layer, x, y, color, 0x20, text);
}
