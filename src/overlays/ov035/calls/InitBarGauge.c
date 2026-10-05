#include "nitro/types.h"

typedef struct PaletteHeader {
    u8 unknown_00[0x14];
    const void *data;
} PaletteHeader;

typedef struct GaugeWork {
    void *source;
    void *buffer;
    void *cells;
    void *frameFile;
    PaletteHeader *frameHeader;
    u8 unknown_14[4];
    int level;
    u8 unknown_1c[0x114];
    int target;
    int current;
} GaugeWork;

typedef struct GaugeGlobals {
    void *unknown_00;
    GaugeWork *work;
} GaugeGlobals;

extern GaugeGlobals data_ov035_020bc508;
extern void *GetSceneTagTracker(void);
extern GaugeWork *NNSi_FndGetCurrentRootHeap(void);
extern u32 MakePrimaryVramKey(u32 slot);
extern void *func_0202c4a0(u32 fileId, u32 alignFlag);
extern int NNS_G2dGetUnpackedBGCharacterData(void *file, PaletteHeader **header);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void MIi_CpuClearFast(int value, void *dest, u32 size);
extern void UpdateBarGauge(GaugeWork *work);
extern void *FindLoadedElementById(void *pool, int id);
extern void SetTagRecordArmed(void *pool, void *record, int armed);
extern void *FindActiveRecordById(void *pool, int id);
extern void func_ov027_020b8230(void *pool, void *record);
extern void UpdateGaugeFrame(void);

void *InitBarGauge(void) {
    PaletteHeader *header;
    void *pool = GetSceneTagTracker();
    GaugeWork *work = NNSi_FndGetCurrentRootHeap();
    void *file;

    data_ov035_020bc508.work = work;
    work->level = 0;
    work->current = 0;
    work->target = 0;
    file = func_0202c4a0(MakePrimaryVramKey(7), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(file, &header);
    work->source = NNSi_FndAllocFromDefaultHeap(0x160);
    work->buffer = NNSi_FndAllocFromDefaultHeap(0x160);
    MIi_CpuCopyFast(header->data, work->source, 0x160);
    NNSi_FndFreeFromDefaultHeap(file);
    work->frameFile = func_0202c4a0(MakePrimaryVramKey(0xe), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(work->frameFile, &work->frameHeader);
    work->cells = NNS_FndAllocFromDefaultExpHeapEx(0xc0, -4);
    MIi_CpuClearFast(0, work->cells, 0xc0);
    UpdateBarGauge(work);
    SetTagRecordArmed(pool, FindLoadedElementById(pool, 1), 0);
    func_ov027_020b8230(pool, FindActiveRecordById(pool, 5));
    return UpdateGaugeFrame;
}
