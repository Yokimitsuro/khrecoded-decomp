#include "nitro/types.h"

typedef struct {
    u8 mode;
    u8 pad_01[3];
    s32 timer;
} SceneControl;

typedef struct {
    u8 pad_000[0x9ac];
    u64 stateFlags;
} PlayerEntry;

extern s32 func_ov001_02087950(void);
extern s32 func_ov001_0208796c(s32 startIndex);
extern int func_ov001_02087ca0(u32 id);
extern void func_ov001_02087d74(u32 id, u32 state);
extern PlayerEntry *func_ov001_0206db5c(int index);
extern BOOL func_ov046_020c2fcc(void);

void ClearStageEventsAndPlayerFlags(SceneControl *control)
{
    s32 record;
    int i;

    for (record = func_ov001_02087950(); record != 0; record = func_ov001_0208796c(record)) {
        if (func_ov001_02087ca0(record)) {
            func_ov001_02087d74(record, 9);
        }
    }
    control->timer = 0;
    control->mode = 7;
    for (i = 0; i < 3; i++) {
        func_ov001_0206db5c(i)->stateFlags &= ~0x20000000ULL;
    }
    func_ov046_020c2fcc();
}
