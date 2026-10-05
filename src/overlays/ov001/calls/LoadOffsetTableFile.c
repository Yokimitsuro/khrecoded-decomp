#include "nitro/types.h"

typedef struct {
    u8 count;
    u8 pad_01[3];
    u32 offsets[1];
} OffsetTableFile;

typedef struct {
    OffsetTableFile *file;
} OffsetTableHolder;

extern OffsetTableHolder *data_ov001_020a049c;
extern char sOv001_Im_0209eb00[];
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern u8 *func_ov001_020636e4(void);
extern u32 findSharedResourceByName(u8 *table, char *name);
extern OffsetTableFile *Archive_LoadFile(u32 fileId, u32 flags);

void LoadOffsetTableFile(void)
{
    OffsetTableHolder *holder = NNSi_FndAllocFromDefaultHeap(sizeof(OffsetTableHolder));
    int i = 0;
    u8 *base;
    u32 index;
    OffsetTableFile *file;

    MIi_CpuClearFast(0, holder, sizeof(OffsetTableHolder));
    base = func_ov001_020636e4();
    index = findSharedResourceByName(func_ov001_020636e4(), sOv001_Im_0209eb00);
    file = Archive_LoadFile((0x80000000 | (((u32)base + 0x8000) & 0xfffffc) << 7) | (index & 0x1ff), 2);
    holder->file = file;
    for (; i < file->count; i++) {
        file->offsets[i] = (u32)((u8 *)file + file->offsets[i]);
    }
    data_ov001_020a049c = holder;
}
