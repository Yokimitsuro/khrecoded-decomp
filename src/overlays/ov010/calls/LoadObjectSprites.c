#include "nitro/types.h"

typedef struct SpriteLoadDesc {
    const char *name;
    u32 cellFile;
    s32 count;
    u32 charFile;
    u32 param;
} SpriteLoadDesc;

typedef struct SpriteFileEntry {
    u32 param;
    s32 count;
} SpriteFileEntry;

typedef struct SpriteFileTable6 {
    SpriteFileEntry entries[6];
} SpriteFileTable6;

typedef struct SpriteOwner {
    u8 pad_00[0x2c];
    u32 archive;
    s16 spriteIds[6];
} SpriteOwner;

extern SpriteFileTable6 data_ov010_020a1d4c;
extern s16 func_ov021_020a89c8(SpriteLoadDesc *desc);

#define SPRITE_FILE(archive, index) \
    ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void LoadObjectSprites(SpriteOwner *owner)
{
    SpriteLoadDesc desc;
    SpriteFileTable6 table;
    int i;

    table = data_ov010_020a1d4c;
    for (i = 0; i < 6; i++) {
        desc.charFile = SPRITE_FILE(owner->archive, i * 2);
        desc.cellFile = SPRITE_FILE(owner->archive, i * 2 + 1);
        desc.count = table.entries[i].count;
        desc.param = table.entries[i].param;
        owner->spriteIds[i] = func_ov021_020a89c8(&desc);
    }
}
