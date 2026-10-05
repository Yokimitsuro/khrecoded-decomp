#include "nitro/types.h"

#define ARCHIVE_FILE_ID(archive, index) ((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct {
    u8 pad_00[2];
    u16 useCount;
} SharedRecord;

typedef struct {
    u8 pad_000[0x20];
    u8 renderObj[0x2c];
    void *renderUser;
    u8 pad_050[0xb4];
    u8 recordState[0x2c];
    s8 slot;
    s8 active;
    u8 pad_132[0x1a];
} SlotMarker;

extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern u32 func_ov001_0206dba0(u32 index);
extern SharedRecord *SND_RegisterSeq(u32 key, u32 context);
extern void *func_0202c4a0(u32 fileId, u32 mode);
extern void func_0202edb0(SlotMarker *object, SharedRecord *record, void *block, u32 context);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void NNS_G3dRenderObjSetCallBack(void *renderObj, void (*func)(void *rs), u8 *unused, u8 cmd, int timing);
extern void OverrideNodeTranslation(void *rs);
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern void AcquireSharedRecordState(void *state, u32 key, u32 initArg, u32 context);

void InitSlotMarker(SlotMarker *marker, u32 slot)
{
    SharedRecord *record;
    void *block = NULL;

    MI_CpuFill8(marker, 0, sizeof(SlotMarker));
    marker->slot = slot;
    *(u32 *)marker->recordState = 0;
    marker->active = 0;
    record = SND_RegisterSeq(ARCHIVE_FILE_ID(func_ov001_0206dba0(2), 2), slot + 8);
    if (record->useCount == 0) {
        block = func_0202c4a0(ARCHIVE_FILE_ID(func_ov001_0206dba0(2), 3), 0x11);
    }
    func_0202edb0(marker, record, block, slot + 8);
    if (block != NULL) {
        NNSi_FndFreeFromDefaultHeap(block);
    }
    marker->renderUser = marker;
    NNS_G3dRenderObjSetCallBack(marker->renderObj, OverrideNodeTranslation, NULL, 6, 3);
    GetOverlaySelectionRecord(slot);
    AcquireSharedRecordState(marker->recordState, ARCHIVE_FILE_ID(func_ov001_0206dba0(1), 0), (u32)marker, slot + 8);
}
