#include "nitro/types.h"

typedef struct {
    u32 offsets[8];
    u32 extraA[2];
    u32 extraB[2];
} MotionBlock;

typedef struct {
    u32 header;
    MotionBlock blocks[3];
} MotionFile;

typedef struct {
    u16 id;
    u16 pad_02;
    u32 value;
} ZoneTag;

typedef struct {
    u8 pad_00[6];
    vu16 tagCount; /* Reread on every loop iteration */
    ZoneTag tags[1];
} ZoneInfo;

typedef struct {
    u32 pad_00;
    ZoneInfo *info;
} ZoneState;

typedef struct {
    u32 state;
    u8 selection;
    u8 pad_05[7];
    u8 motionA[0x20];
    u8 motionB[0x20];
} UnitResources;

extern int func_ov001_02063a38(void);
extern ZoneState *func_ov001_02073060(void);
extern void BuildNodeGraph(void *motion, u8 selection, u32 *extra, u32 *offsets);

void RelocateUnitMotionData(UnitResources *unit, MotionFile *file, int kind)
{
    MotionBlock *block = &file->blocks[0];
    ZoneInfo *info;
    int i;

    if (kind == 0 && func_ov001_02063a38() != 4) {
        info = func_ov001_02073060()->info;
        i = 0;
        while (i < info->tagCount) {
            u16 id = info->tags[i].id;
            if (id == 0x58) {
                block += 1;
                break;
            }
            if (id == 0x57) {
                block += 2;
                break;
            }
            i++;
        }
    }
    block->offsets[0] = (u32)((u8 *)file + block->offsets[0]);
    block->offsets[1] = (u32)((u8 *)file + block->offsets[1]);
    block->offsets[2] = (u32)((u8 *)file + block->offsets[2]);
    block->offsets[3] = (u32)((u8 *)file + block->offsets[3]);
    block->offsets[4] = (u32)((u8 *)file + block->offsets[4]);
    block->offsets[5] = (u32)((u8 *)file + block->offsets[5]);
    block->offsets[6] = (u32)((u8 *)file + block->offsets[6]);
    block->offsets[7] = (u32)((u8 *)file + block->offsets[7]);
    BuildNodeGraph(unit->motionA, unit->selection, block->extraA, &block->offsets[0]);
    BuildNodeGraph(unit->motionB, unit->selection, block->extraB, &block->offsets[4]);
}
