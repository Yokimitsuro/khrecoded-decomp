#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x28cc];
    u32 experience;
    u8 pad_28D0[0x6];
    u8 level;
} SaveData;

typedef struct EventEntry {
    u32 unk_00;
    void *object;
    u8 pad_08[0x20];
} EventEntry;

typedef struct EventContext {
    u32 unk_00;
    EventEntry entries[3];
} EventContext;

extern SaveData *data_0205fe0c;
extern EventContext *data_ov001_020a04bc;
extern u32 GetEntryParam(u8 level);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern u16 func_02029254(int index, const void *src);

int ApplyPendingLevelUps(void)
{
    SaveData *save = data_0205fe0c;
    int level = save->level;
    int step;
    int levelsGained;
    int newLevel;
    int i;

    if (data_ov001_020a04bc->entries[0].object == NULL) {
        return 0;
    }
    if (level >= 50) {
        return 0;
    }
    if (save->experience < GetEntryParam(level)) {
        return 0;
    }
    for (step = 1, levelsGained = 1; step < 50 - level; step++, levelsGained++) {
        save = data_0205fe0c;
        if (save->experience < GetEntryParam(level + step)) {
            break;
        }
    }
    newLevel = level + levelsGained;
    if (newLevel > 50) {
        newLevel = 50;
    } else if (newLevel < 0) {
        newLevel = 0;
    }
    save->level = newLevel;
    if (!IsGlobalPackedBitSet(0x90)) {
        SetGlobalPackedBit(0x90);
    }
    for (i = 0; i < levelsGained; i++) {
        func_02029254(0x90, NULL);
    }
    return levelsGained;
}
