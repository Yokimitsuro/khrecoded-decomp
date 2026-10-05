#include "nitro/types.h"

typedef struct GlyphSource {
    u8 unknown_00[0x14];
    u8 *glyphs;
} GlyphSource;

typedef struct DigitCanvas {
    u8 unknown_00[8];
    u8 *pixels;
    u8 unknown_0c[4];
    GlyphSource *font;
    int dirty;
} DigitCanvas;

extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);

void DrawDigitRow(DigitCanvas *canvas, int row, int value) {
    int i;
    int digit;
    u8 *glyph;
    u8 *dest;
    int count = 0;

    MIi_CpuClearFast(0x11111111, canvas->pixels + row * 0x40, 0x40);
    dest = canvas->pixels + row * 0x40 + 0x22;
    do {
        digit = value % 10;
        value = value / 10;
        glyph = canvas->font->glyphs + digit * 0x20;
        for (i = 0; i < 8; i++) {
            MIi_CpuCopy16(glyph + i * 4, dest + i * 4, 2);
        }
        if (++count % 2 == 0) {
            dest -= 0x1e;
        } else {
            dest -= 2;
        }
    } while (value > 0);
    canvas->dirty = 1;
}
