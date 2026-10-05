#include "nitro/types.h"

extern void func_0202c6a4(int enable);
extern void ValidateResourceTagAndDispatch(void *resource, int arg);
extern void *NNS_G3dGetTex(void *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

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

void RebindSpriteToCell(u16 *sprite, BOOL freeResource, BOOL stopAnimation, u32 cellIndex)
{
    int resource;
    u32 *cell;
    u16 *attr;
    u32 width;
    u32 height;
    u32 origin;

    if (stopAnimation) {
        func_0202c6a4(0);
        ValidateResourceTagAndDispatch(*(void **)(sprite + 0x14), 0);
        func_0202c6a4(1);
    }

    *(u8 *)(sprite + 0x13) = (u8)(*(u8 *)(sprite + 0x13) & ~0xe0);

    resource = (int)NNS_G3dGetTex(*(void **)(sprite + 0x14));
    if (resource != 0) {
        cell = (u32 *)GetResourceSection(resource + 0x3c, 1, 6, cellIndex);
    } else {
        cell = 0;
    }

    if (resource != 0 && *(u16 *)(resource + 0x34) != 0) {
        attr = (u16 *)GetResourceSection(resource + *(u16 *)(resource + 0x34), 1, 6, 0);
    } else {
        attr = 0;
    }

    height = *(u32 *)(resource + 0x2c) & 0xffff;
    width = attr[0];
    if ((u8)((cell[0] & 0x1c000000) >> 26) == 5) {
        origin = *(u32 *)(resource + 0x18) & 0xffff;
    } else {
        origin = *(u32 *)(resource + 8) & 0xffff;
    }
    if ((attr[1] & 1) == 0) {
        width = (width << 0xf) >> 0x10;
        height = (height << 0xf) >> 0x10;
    }

    sprite[0] = (u16)(cell[1] & 0x7ff);
    sprite[1] = (u16)((cell[1] >> 0xb) & 0x7ff);
    *(u32 *)(sprite + 4) = (cell[0] + origin) | 0x20000000;
    *(u32 *)(sprite + 6) = (width + height) & 0xffff;
    sprite[2] = (u16)((short *)sprite)[0];
    sprite[3] = (u16)((short *)sprite)[1];
    *(u32 *)((u8 *)sprite + 0x20) = 0;
    *((u8 *)sprite + 0x25) = 0;
    *(u32 *)((u8 *)sprite + 0x18) = 0x1000;
    *(u32 *)((u8 *)sprite + 0x1c) = 0x1000;
    *(u8 *)(sprite + 0x13) = (u8)((*(u8 *)(sprite + 0x13) & ~0x1f) | 0x1f);

    if (freeResource) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(sprite + 0x14));
    }
    *(u32 *)(sprite + 0x14) = 0;
}
