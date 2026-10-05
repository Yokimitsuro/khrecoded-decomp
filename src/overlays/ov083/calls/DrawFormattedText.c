#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

typedef struct Ov083State {
    u8 pad_00[0xb8];
    u8 window[0x34];
} Ov083State;

extern void Text_VSNPrintfWide(u16 *dst, u32 length, const u16 *format, va_list args);
extern void DrawTextAnchored(void *window, int x, int y, int color, u32 flags, const u16 *text);

void DrawFormattedText(Ov083State *state, int x, int y, int color, const u16 *format, ...)
{
    u16 text[0x10];
    va_list args;

    va_start(args, format);
    Text_VSNPrintfWide(text, 0x10, format, args);
    DrawTextAnchored(state->window, x, y, color, 0x20, text);
}