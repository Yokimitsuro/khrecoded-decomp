#include "nitro/types.h"

typedef struct PzOwner {
    u8 pad_000[0x210];
    void *pzResource;
} PzOwner;

extern u8 *func_ov001_020636e4(void);
extern int findSharedResourceByName(u8 *table, const char *name);
extern void *Archive_LoadFile(u32 fileId, u32 heapId);
extern char sOv001_Pz_0209ea10[];

void LoadPzResource(PzOwner *owner)
{
    u8 *archive;
    int entryIndex;

    archive = func_ov001_020636e4();
    entryIndex = findSharedResourceByName(func_ov001_020636e4(), sOv001_Pz_0209ea10);
    owner->pzResource =
        Archive_LoadFile(((((u32)(archive + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (entryIndex & 0x1ff), 5);
}
