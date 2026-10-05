#include "nitro/types.h"

typedef struct {
    s32 mode;
    s32 count;
    u8 pad_08[4];
    s32 radius;
    s32 scaleX;
    u8 pad_14[8];
    s32 scaleY;
    u8 pad_20[0x10];
    s32 enabled;
    u8 pad_34[0xc];
    s32 extentX;
    s32 extentY;
    s32 extentZ;
    u8 pad_4c[0xc];
    s16 linkA;
    s16 linkB;
    u8 entryCount;
    u8 pad_5d[3];
} UnitParams;

typedef struct {
    u8 pad_00[0x2c];
    void *updateCallback;
} UnitModel;

typedef struct {
    u8 pad_00[0x54];
    s32 archive;
    UnitModel *model;
} EffectUnit;

extern void ResetMotionState(UnitParams *params);
extern void SetupOwnerAndEntries(UnitModel *model, u32 fileA, u32 fileB, UnitParams *params, int argA, int argB);
extern void AdvanceTimedHitUnit(void);

#define ARCHIVE_FILE(archive, index) ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void SetupUnitEffectModel(void *unused, EffectUnit *unit)
{
    UnitParams params;

    ResetMotionState(&params);
    params.mode = 0x1006;
    params.count = 2;
    params.scaleX = 0xa000;
    params.scaleY = 0xa000;
    params.radius = 0x2600;
    params.linkA = -1;
    params.linkB = -1;
    params.extentY = 0;
    params.extentX = 0x100;
    params.enabled = 1;
    params.extentZ = 0x100;
    params.entryCount = 2;
    SetupOwnerAndEntries(unit->model, ARCHIVE_FILE(unit->archive, 0), ARCHIVE_FILE(unit->archive, 1), &params, 1, 2);
    unit->model->updateCallback = AdvanceTimedHitUnit;
}
