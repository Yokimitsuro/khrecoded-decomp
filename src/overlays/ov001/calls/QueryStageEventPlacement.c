#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventPlacement {
    VecFx32 position;
    u32 unkC;
    u16 direction;
    u16 unk12;
} EventPlacement;

extern int data_ov001_0209f2e8;
extern u8 *GetStageEventRecord(u32 id);
extern void MI_CpuFill8(void *dest, u8 value, u32 size);
extern int func_ov001_02096644(u8 *record, int arg, EventPlacement *placement);

int QueryStageEventPlacement(u32 id, int arg, VecFx32 *position, u16 *direction) {
    EventPlacement placement;
    u8 *record;
    int result;

    if (data_ov001_0209f2e8 != -1) {
        record = GetStageEventRecord(id);
        MI_CpuFill8(&placement, 0, sizeof(EventPlacement));
        if (record != NULL) {
            result = func_ov001_02096644(record, arg, &placement);
            if (position != NULL) {
                *position = placement.position;
            }
            if (direction != NULL) {
                *direction = placement.direction;
            }
            return result;
        }
    }
    return 0;
}
