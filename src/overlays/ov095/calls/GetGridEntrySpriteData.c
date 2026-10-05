#include "nitro/types.h"

typedef struct {
    u8 header[8];
    u8 data[1];
} SpriteResource;

typedef struct {
    u8 pad[0x30];
    SpriteResource *resource;
    u8 rest[0x58];
} GridSprite;

typedef struct {
    u8 pad[0x18];
    GridSprite sprites[(0x6434 - 0x18) / 0x8c];
    u8 tail[0x6434 - 0x18 - ((0x6434 - 0x18) / 0x8c) * 0x8c];
} GridLayer;

typedef struct {
    u8 pad[0x180];
    GridLayer layers[2];
} GridWork;

extern int *GetGridEntry(int layer, int index, GridWork *work);

void *GetGridEntrySpriteData(int layer, int index, GridWork *work) {
    GridLayer *gridLayer = &work->layers[layer];
    int *entry = GetGridEntry(layer, index, work);
    GridSprite *sprite;
    void *data;

    if (*entry < 0) {
        return NULL;
    }
    sprite = &gridLayer->sprites[*entry];
    if (sprite == NULL) {
        return NULL;
    }
    if (sprite->resource == NULL) {
        return NULL;
    }
    data = sprite->resource->data;
    if (data == NULL) {
        return NULL;
    }
    return data;
}