#include "nitro/types.h"

#define ARCHIVE_FILE_ID(archive, index) \
    (((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000) | ((index) & 0x1ff))

typedef struct {
    u32 initialized;
    void *record;
    u8 state[0x24];
} SharedRecordState;

typedef struct {
    u8 pad_000[0x104];
    SharedRecordState sharedState;
    BOOL isActive;
} EffectSlot;

typedef struct {
    u8 pad_00[2];
    u16 isLoaded;
} SharedRecord;

typedef struct {
    u8 pad_00[0x38];
    u32 archive;
} OverlayState;

extern OverlayState data_ov058_020d8a44;

extern SharedRecord *SND_RegisterSeq(u32 fileId, int context);
extern void *func_0202c4a0(u32 fileId, u32 flags);
extern void func_0202edb0(EffectSlot *slot, SharedRecord *record, void *data, int context);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void AcquireSharedRecordState(SharedRecordState *state, u32 fileId, EffectSlot *slot, int context);

void LoadArchiveEffectSlot(EffectSlot *slot, u32 fileIndex)
{
    OverlayState *state = &data_ov058_020d8a44;
    void *data = NULL;
    SharedRecord *record = SND_RegisterSeq(ARCHIVE_FILE_ID(state->archive, 0), 6);

    if (record->isLoaded == 0) {
        data = func_0202c4a0(ARCHIVE_FILE_ID(state->archive, 1), 0x11);
    }
    func_0202edb0(slot, record, data, 6);
    if (data != NULL) {
        NNSi_FndFreeFromDefaultHeap(data);
    }
    slot->sharedState.initialized = 0;
    AcquireSharedRecordState(&slot->sharedState, ARCHIVE_FILE_ID(state->archive, fileIndex), slot, 6);
    slot->isActive = FALSE;
}
