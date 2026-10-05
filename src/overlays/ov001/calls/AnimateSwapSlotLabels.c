#include "nitro/types.h"

typedef struct SwapAnimator {
    u8 pad_00[0x20];
    u16 slotIds[2];
    u8 pad_24[2];
    u16 step : 14;
    u16 flags : 2;
    u8 pad_28[4];
    int side;
} SwapAnimator;

extern const int data_ov001_0209e000[];
extern const int data_ov001_0209e010[];

extern void *GetSceneTagTracker(void);
extern int func_ov001_0207123c(void);
extern void func_ov027_020b9d74(int screen, int layer, int x, int y, int width, int height);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8200(void *pool, void *record, s16 y);
extern void func_ov027_020b8230(void *pool, void *record);

void AnimateSwapSlotLabels(SwapAnimator *anim)
{
    void *pool = GetSceneTagTracker();
    int screen = func_ov001_0207123c();
    void *record;

    if (anim->step != 0 && anim->step <= 3) {
        func_ov027_020b9d74(screen, 0xb, 0xe, 0xf, 4, 7);
        if (anim->step < 3) {
            record = FindActiveRecordById(pool, data_ov001_0209e000[anim->slotIds[anim->side]]);
            func_ov027_020b8200(pool, record, 0x13 - anim->step);
        } else {
            record = FindActiveRecordById(pool, data_ov001_0209e010[anim->slotIds[anim->side]]);
            func_ov027_020b8200(pool, record, 0xf);
            func_ov027_020b8230(pool, record);
            record = FindActiveRecordById(pool, data_ov001_0209e000[anim->slotIds[anim->side ^ 1]]);
            func_ov027_020b8200(pool, record, 0x13);
        }
        func_ov027_020b8230(pool, record);
        anim->step++;
    }
}
