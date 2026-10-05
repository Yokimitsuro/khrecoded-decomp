#include "nitro/types.h"

typedef struct SpriteSource {
    u8 pad_00[0x10];
    int resource;
} SpriteSource;

static inline void *GetResourceSection(int section, int countOffset, int tableOffset, u32 index)
{
    u32 stride;
    int table;

    if (section != 0 && index < *(u8 *)(section + countOffset)) {
        table = section + *(u16 *)(section + tableOffset);
        stride = *(u16 *)table;
        return (void *)(table + 4 + stride * index);
    }
    return 0;
}

void BindSlotToSourceCell(u16 *slot, SpriteSource *source)
{
    int resource;
    u32 *cell;
    u16 *attr;
    u32 width;
    u32 height;
    u32 origin;

    *(u8 *)(slot + 0x15) = (u8)(*(u8 *)(slot + 0x15) & ~0xe0);

    resource = source->resource;
    if (resource != 0) {
        cell = (u32 *)GetResourceSection(resource + 0x3c, 1, 6, 0);
    } else {
        cell = 0;
    }

    if (resource != 0 && *(u16 *)(resource + 0x34) != 0) {
        attr = (u16 *)GetResourceSection(resource + *(u16 *)(resource + 0x34), 1, 6, 0);
    } else {
        attr = 0;
    }

    width = attr[0];
    height = *(u32 *)(resource + 0x2c) & 0xffff;
    if ((u8)((cell[0] & 0x1c000000) >> 26) == 5) {
        origin = *(u32 *)(resource + 0x18) & 0xffff;
    } else {
        origin = *(u32 *)(resource + 8) & 0xffff;
    }
    if ((attr[1] & 1) == 0) {
        width = (width << 0xf) >> 0x10;
        height = (height << 0xf) >> 0x10;
    }

    slot[0] = (u16)(cell[1] & 0x7ff);
    slot[1] = (u16)((cell[1] >> 0xb) & 0x7ff);
    *(u32 *)(slot + 4) = (cell[0] + origin) | 0x20000000;
    *(u32 *)(slot + 6) = (width + height) & 0xffff;
    slot[2] = (u16)((short *)slot)[0];
    slot[3] = (u16)((short *)slot)[1];
    *(u32 *)((u8 *)slot + 0x20) = 0;
    *((u8 *)slot + 0x25) = 0;
    *(u32 *)((u8 *)slot + 0x18) = 0x1000;
    *(u32 *)((u8 *)slot + 0x1c) = 0x1000;
    slot[0x14] = 0;
    slot[0x13] = slot[0x14];
    *(u8 *)(slot + 0x15) = (u8)((*(u8 *)(slot + 0x15) & ~0x1f) | 0x1f);
    *(u32 *)(slot + 0x16) = 0;
}
