#include "nitro/types.h"

typedef struct RecordViewer {
    u8 pad_000[0x64];
    u8 records[0xce];
    s16 selectedId;
    s8 selectedSlot;
    u8 pad_135[0x1c8 - 0x135];
} RecordViewer;

extern RecordViewer *data_ov001_020a04fc;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void AcquireRecordSlot(int slot, int mode);
extern void *GetRecordTableEPointer(void);
extern void ReleaseRecordSlot(int slot);

void CreateRecordViewer(void)
{
    data_ov001_020a04fc = NNSi_FndAllocFromDefaultHeap(sizeof(RecordViewer));
    MIi_CpuClearFast(0, data_ov001_020a04fc, sizeof(RecordViewer));
    data_ov001_020a04fc->selectedId = -1;
    data_ov001_020a04fc->selectedSlot = -1;
    AcquireRecordSlot(12, 1);
    MI_CpuCopy8(GetRecordTableEPointer(), data_ov001_020a04fc->records, sizeof(data_ov001_020a04fc->records));
    ReleaseRecordSlot(12);
}

