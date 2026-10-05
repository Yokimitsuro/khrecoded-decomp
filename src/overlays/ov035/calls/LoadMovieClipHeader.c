#include "nitro/types.h"

#define ARCHIVE_FILE_ID(archive, index) ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

typedef struct MovieSubHeader {
    u32 unknown_00;
    u32 offsetA;
    u32 offsetB;
    u32 offsetC;
} MovieSubHeader;

typedef struct MovieHeader {
    u32 unknown_00;
    u32 sub;
} MovieHeader;

typedef struct MovieWork {
    u8 unknown_00[0x1d];
    u8 eventMode;
    s8 clipIndex;
    u8 unknown_1f[7];
    s16 eventId;
    u8 unknown_28[0x10];
    MovieHeader *header;
    u8 unknown_3c[0x8c];
    u8 soundState;
} MovieWork;

extern MovieWork *data_ov035_020bc500;
extern char sOv035_RpgZ_020bc4c0[];
extern u8 func_ov035_020bb110(void);
extern u32 func_ov001_020636e4(void);
extern int findSharedResourceByName(unsigned char *table, void *name);
extern u32 func_0202c4a0(u32 fileId, u32 alignFlag);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadMovieClipHeader(void) {
    MovieWork *work = data_ov035_020bc500;
    u32 archive;
    int index;
    u8 *file;
    u32 offset;
    MovieSubHeader *sub;

    work->eventMode = 0;
    work->eventId = -1;
    work->soundState = func_ov035_020bb110();
    archive = func_ov001_020636e4();
    index = findSharedResourceByName((unsigned char *)archive, sOv035_RpgZ_020bc4c0);
    file = (u8 *)func_0202c4a0(ARCHIVE_FILE_ID(archive, index), 2);
    offset = ((u32 *)(file + 4))[work->clipIndex - 1];
    work->header = NNSi_FndAllocFromDefaultHeap(*(u16 *)(file + offset));
    MI_CpuCopy8(file + offset, work->header, *(u16 *)(file + offset));
    work->header->sub += (u32)work->header;
    sub = (MovieSubHeader *)work->header->sub;
    sub->offsetA += (u32)sub;
    sub = (MovieSubHeader *)work->header->sub;
    sub->offsetB += (u32)sub;
    sub = (MovieSubHeader *)work->header->sub;
    sub->offsetC += (u32)sub;
    NNSi_FndFreeFromDefaultHeap(file);
}
