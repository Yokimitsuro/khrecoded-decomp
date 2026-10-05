#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 unk_00_2 : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef union {
    u32 raw;
    struct {
        s16 type;
        s16 id;
    } f;
} RewardKey;

typedef struct {
    RewardKey key;
    u16 level;
    u16 kind;
    u32 extra;
} Reward;

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern u16 func_02029254(int index, const void *src);
extern void SetGlobalPackedBit(int bitIndex);
extern s32 PickRandomRecordWithBias(s32 category);
extern s32 IsRecordFlagBitSet(s32 recordId);
extern u32 DispatchContextCommand(u32 command, u32 value, u32 extra, void *buffer);
extern u32 func_ov002_02066c68(u32 argument0);

BOOL GrantRewardEntry(Reward *dst, const Reward *src)
{
    RewardKey key;
    RecordEntry entry;
    int status;
    BOOL granted;

    key.raw = src->key.raw;
    granted = FALSE;
    if (key.f.type == 0) {
        int id = key.f.id;
        u16 added;

        if (id >= 0 && id <= 0x7f) {
            MI_CpuFill8(&entry, 0, sizeof(RecordEntry));
            entry.level = src->level;
            entry.kind = src->kind;
            added = func_02029254(id, &entry);
        } else {
            added = func_02029254(id, NULL);
        }
        SetGlobalPackedBit(id);
        if (added != 0) {
            granted = TRUE;
        }
    } else if (key.f.type == 9) {
        s32 id = PickRandomRecordWithBias(key.f.id);
        key.f.id = id;
        if (!IsRecordFlagBitSet(id)) {
            DispatchContextCommand(0x8000000c, id, 0, &status);
            if (status != 0) {
                granted = TRUE;
            }
        }
    }
    *dst = *src;
    dst->key.raw = key.raw;
    if (granted) {
        func_ov002_02066c68(1);
    }
    return granted;
}
