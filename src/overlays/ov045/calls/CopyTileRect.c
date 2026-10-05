#include "nitro/types.h"

typedef struct {
    u8 pad00[0x34];
    BOOL dirty;
    u8 pad38[0x4c];
    u16 layerB[0x600];
    u16 layerA[0x600];
} TileLayers;

typedef struct {
    u16 header;
    u8 pad02[0xa];
    u16 tiles[1];
} ScreenData;

typedef struct {
    u8 pad00[8];
    ScreenData *screen;
} ScreenResource;

typedef struct {
    u16 pad00;
    s16 x;
    s16 y;
    u16 srcX;
    u16 srcY;
    s16 width;
    s16 height;
    u16 pad0e;
    int layer;
    u8 pad14[4];
    ScreenResource *resource;
} TileRect;

extern TileLayers *data_ov045_020c08a0;

extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);

void CopyTileRect(TileRect *rect)
{
    u32 size;
    TileLayers *layers = data_ov045_020c08a0;
    u16 *tiles;

    if (rect->layer == 11) {
        tiles = layers->layerB;
    } else if (rect->layer == 10) {
        tiles = layers->layerA;
    } else {
        tiles = NULL;
    }
    if (tiles != NULL) {
        s16 rows;
        u16 *src;
        u16 stride;
        ScreenData *screen;

        size = (u16)(rect->width * 2);
        screen = rect->resource->screen;
        stride = screen->header >> 3;
        src = screen->tiles + rect->srcX + rect->srcY * stride;

        tiles = tiles + rect->x + rect->y * 32;
        for (rows = rect->height; rows > 0; rows--) {
            MIi_CpuCopy16(src, tiles, size);
            src += stride;
            tiles += 32;
        }
        layers->dirty = TRUE;
    }
}
