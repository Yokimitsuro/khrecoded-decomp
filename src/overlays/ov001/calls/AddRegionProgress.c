#include "nitro/types.h"

typedef struct RegionProgress {
    u8 region;
    u8 pad_01[0xd];
    u8 level;
    u8 pad_0f;
    u16 thresholds[4];
} RegionProgress;

typedef struct SelectionRecord {
    u8 pad_00[0x10];
    RegionProgress progress;
} SelectionRecord;

typedef struct ProgressBlock {
    u8 pad_000[0x4dc];
    u16 recordIndex;
    u8 pad_4de[0x2a];
    u16 points[8];
} ProgressBlock;

typedef struct GameState {
    u8 pad_0000[0x28d8];
    ProgressBlock block;
} GameState;

extern GameState *data_0205fe0c;
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov001_020644b0(void);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void DecrementByteCounter(int index);
extern u16 func_02029254(int index, const void *src);
extern void func_ov001_02072530(u32 choice);

static inline BOOL IsRegionMilestoneReady(void)
{
    BOOL ready = FALSE;

    if (func_ov001_020644b0() == 900) {
        ready = TRUE;
    }
    return ready;
}

void AddRegionProgress(int amount)
{
    RegionProgress *progress;
    ProgressBlock *block;
    u16 points;

    if (amount == 0) {
        return;
    }
    if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a) || func_ov001_020645c8(0x360b)) {
        return;
    }
    progress = &GetOverlaySelectionRecord(0)->progress;
    if (progress->level >= 4) {
        return;
    }
    block = &data_0205fe0c->block;
    points = block->points[progress->region];
    points = points + amount;
    block->points[progress->region] = points;
    if (points >= progress->thresholds[progress->level]) {
        progress->level++;
        DecrementByteCounter(block->recordIndex);
        block->recordIndex++;
        func_02029254(block->recordIndex, NULL);
        func_ov001_02072530(progress->level);
        block->points[progress->region] = 0;
        if (progress->region == 0 && progress->level == 1 && IsRegionMilestoneReady()) {
            WriteSessionPackedBits(0x380a, 1, 1);
        }
    }
    if (progress->level == 4) {
        WriteSessionPackedBits(progress->region + 0xbd9, 1, 1);
    }
}
