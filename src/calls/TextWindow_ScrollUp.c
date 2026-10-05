#include "nitro/types.h"

struct CharCanvas;

typedef struct CharCanvasVTable {
    void (*drawGlyph)(void);
    void (*clear)(const struct CharCanvas *canvas, int color);
    void (*clearArea)(const struct CharCanvas *canvas, int color, int x, int y, int width, int height);
} CharCanvasVTable;

typedef struct CharCanvas {
    u8 pad_00[0x14];
    const CharCanvasVTable *vtable;
} CharCanvas;

typedef struct TextSurface {
    u8 pad_00[0xC];
    CharCanvas canvas;
    u8 *chars;
} TextSurface;

typedef struct TextWindow {
    u8 pad_00[0x20];
    TextSurface *surface;
    u8 pad_24[4];
    u32 size;
    u8 pad_2C[2];
    u16 areaWidth;
    u16 areaHeight;
    u8 charSize;
} TextWindow;

extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);

void TextWindow_ScrollUp(TextWindow *win, int n)
{
    int rows = n / 8;
    int lines = n % 8;
    int rowBytes;
    int lineBytes;
    int y;
    int x;
    u8 *cell;
    CharCanvas *canvas;

    if (rows > 0) {
        int shift = rows * (win->charSize * win->areaWidth);

        MIi_CpuCopyFast(win->surface->chars + shift, win->surface->chars, win->size - shift);
    }
    rowBytes = win->areaWidth * win->charSize;
    lineBytes = ((u32)win->charSize >> 3) * lines;
    for (y = 0; y < win->areaHeight; y++) {
        cell = win->surface->chars + rowBytes * y;
        MIi_CpuCopyFast(cell + lineBytes, cell, rowBytes - lineBytes);
        cell += rowBytes;
        for (x = 0; x < win->areaWidth; x++) {
            MIi_CpuCopy32(cell, cell - rowBytes + win->charSize - lineBytes, lineBytes);
            cell += win->charSize;
        }
    }
    canvas = &win->surface->canvas;
    canvas->vtable->clearArea(canvas, 0, 0, (win->areaHeight << 3) - n, win->areaWidth << 3, n);
}
