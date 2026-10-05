#include "nitro/types.h"

typedef struct {
    u8 data[0x38];
} TextSurface;

typedef struct {
    u8 pad_00[0x34];
    TextSurface surface;
    const u16 *cursor;
    u8 pad_70[4];
    int penX;
} TextWriter;

extern int ForwardInnerPayload(TextSurface *surface, int x, int y, int color, u16 glyph);
extern void Text_UploadTileBuffer(TextSurface *surface);

BOOL DrawNextTypewriterGlyph(TextWriter *writer) {
    if (*writer->cursor == 0) {
        return FALSE;
    }
    writer->penX += ForwardInnerPayload(&writer->surface, writer->penX, 3, 2, *writer->cursor);
    Text_UploadTileBuffer(&writer->surface);
    writer->cursor++;
    return TRUE;
}
