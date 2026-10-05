#include "nitro/types.h"

typedef struct SharedRecordState {
    u32 initialized;
    void *record;
    u8 state[0x24];
} SharedRecordState;

typedef struct RecordHeader {
    u8 pad_00[0x10];
    s32 loadedData;
} RecordHeader;

typedef struct Unit {
    u8 pad_00[0x134];
    void *recordState;
    u8 pad_138[0x154 - 0x138];
} Unit;

typedef struct UnitOwner {
    u8 pad_00[0x08];
    Unit *units;
    u8 pad_0C[0x09];
    u8 unitCount;
    u8 pad_16[0x44 - 0x16];
    u8 model[0x148 - 0x44];
    SharedRecordState ownerState;
    SharedRecordState *unitStates;
} UnitOwner;

extern u32 func_ov001_0206dba0(int index);

#define ARCHIVE_FILE_KEY(id) (0x80000000 | (((func_ov001_0206dba0(0) + 0x8000) & 0xFFFFFC) << 7) | (id))
extern void *SND_RegisterSeq(u32 key, void *context);
extern void *func_0202c4a0(u32 key, u32 flags);
extern void func_0202edb0(void *object, void *record, void *data, void *context);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void AcquireSharedRecordState(SharedRecordState *state, u32 key, void *object, void *context);

void LoadUnitSharedRecords(UnitOwner *owner, u32 fileId, u8 *archive)
{
    void *context = archive + 8;
    RecordHeader *record;
    Unit *unit;
    u32 stateId;
    int index;

    record = SND_RegisterSeq(ARCHIVE_FILE_KEY(fileId & 0x1FF), context);
    if (record->loadedData != 0) {
        func_0202edb0(owner->model, record, NULL, context);
    } else {
        void *data = func_0202c4a0(ARCHIVE_FILE_KEY((fileId + 2) & 0x1FF), 0x11);
        func_0202edb0(owner->model, record, data, context);
        NNSi_FndFreeFromDefaultHeap(data);
    }
    stateId = (fileId + 1) & 0x1FF;
    index = 0;
    AcquireSharedRecordState(&owner->ownerState, ARCHIVE_FILE_KEY(stateId), owner->model, context);
    if (owner->unitCount != 0) {
        owner->unitStates = NNSi_FndAllocFromDefaultHeap(owner->unitCount * sizeof(SharedRecordState));
        for (; index < owner->unitCount; index++) {
            SharedRecordState *state;

            unit = &owner->units[index];
            state = &owner->unitStates[index];
            state->initialized = 0;
            AcquireSharedRecordState(state, ARCHIVE_FILE_KEY(stateId), owner->model, context);
            unit->recordState = state->state;
        }
    }
}
