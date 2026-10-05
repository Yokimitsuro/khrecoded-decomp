#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEntryObject StageEntryObject;
typedef BOOL (*StageEntryCheck)(StageEntryObject *entry, u32 arg);

struct StageEntryObject {
    u8 pad_000[0x208];
    StageEntryCheck check;
    u8 pad_20c[0x9e0 - 0x20c];
    VecFx32 direction;
};

extern void *data_ov001_020a0528;

extern StageEntryObject *CacheStageEntryValue(u32 id);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern u16 GetLinkedAngleOffset(StageEntryObject *entry);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern int FX_Atan2Idx(int vertical, int horizontal);

int GetStageEntrySide(u32 id, u32 arg)
{
    StageEntryObject *entry;
    BOOL passed;
    int mode;
    u16 facing;
    u16 angle;
    int delta;
    VecFx32 direction;

    if (data_ov001_020a0528 == NULL) {
        return 0;
    }
    entry = CacheStageEntryValue(id);
    if (entry == NULL) {
        return 0;
    }
    if (entry->check != NULL) {
        passed = entry->check(entry, arg);
    } else {
        passed = FALSE;
    }
    if (!passed) {
        return 0;
    }
    if (func_ov001_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    if (mode == 6) {
        facing = GetLinkedAngleOffset(entry);
        direction = entry->direction;
        direction.y = 0;
        if (direction.x == 0 && direction.y == 0 && direction.z == 0) {
            angle = facing - 0x8000;
        } else {
            VEC_Normalize(&direction, &direction);
            angle = FX_Atan2Idx(-direction.x, -direction.z);
        }
        delta = (u16)(angle - facing);
        if (delta > 0x8000) {
            delta = (u16)(0x10000 - delta);
        }
        if (delta > 0x4000) {
            return 1;
        }
        return -1;
    }
    return 1;
}
