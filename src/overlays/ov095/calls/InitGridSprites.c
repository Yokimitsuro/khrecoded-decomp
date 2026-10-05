#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad0[4];
    u16 width;
    u16 height;
    u8 pad1[8];
    fx32 x;
    fx32 y;
    u8 pad2[8];
    int scale;
    u8 visible;
    u8 pad3[5];
    u8 alpha : 5;
    u8 flags : 3;
    u8 pad4[5];
} SpriteDesc;

typedef struct {
    int archive;
    int index;
} IconEntry;

typedef struct {
    int x;
    int y;
} GridPoint;

typedef struct {
    u8 pad0[8];
    u32 archives[3];
    u8 pad1[0xcaec - 0x14];
    SpriteDesc sprites[0xef];
    GridPoint positions[0xef];
    SpriteDesc badges[0x5d];
} GridWork;

extern const IconEntry data_ov095_020c2130[];
extern BOOL InitSlotFromFile(SpriteDesc *slot, u32 fileId);

#define ARCHIVE_FILE_ID(archive, index) (((index) & 0x1ff) | (((((archive) + 0x8000) & 0xfffffc) << 7) | 0x80000000))
#define INT_TO_FX32_ROUNDED(v) ((fx32)((float)(v) > 0.0f ? 0.5f + 4096.0f * (float)(v) : 4096.0f * (float)(v) - 0.5f))

void InitGridSprites(GridWork *work) {
    int i;

    for (i = 0; i < 0xef; i++) {
        SpriteDesc *sprite = &work->sprites[i];
        const IconEntry *entry = &data_ov095_020c2130[i];

        InitSlotFromFile(sprite, ARCHIVE_FILE_ID(work->archives[entry->archive], entry->index));
        sprite->scale = 0x800;
        sprite->visible = 1;
        sprite->alpha = 0x1f;
        sprite->width = 0x10;
        sprite->height = 0x10;
        sprite->x = INT_TO_FX32_ROUNDED(work->positions[i].x);
        sprite->y = INT_TO_FX32_ROUNDED(work->positions[i].y);
        if (i >= 0x58 && i <= 0xb4) {
            SpriteDesc *badge = &work->badges[i - 0x58];

            InitSlotFromFile(badge, ARCHIVE_FILE_ID(work->archives[entry->archive], 0x2b));
            badge->scale = 0x19a;
            badge->visible = 1;
            badge->alpha = 0x1f;
            badge->width = 0x10;
            badge->height = 0x10;
            badge->x = sprite->x;
            badge->y = sprite->y;
        }
    }
}