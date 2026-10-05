#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[6];
    u16 pad_bits0 : 8;
    u16 armed : 1;
    u16 pad_bits1 : 7;
    u8 pad_008;
    u8 kind;
    u8 area;
    u8 nextArea;
    u8 pad_00c[4];
    s16 actorId;
    u16 objectId;
    u8 pad_014[0x1a2];
    u8 step;
} GateRecord;

typedef struct {
    u8 pad_000[0x2c0];
    VecFx32 position;
} StageActor;

typedef struct {
    u8 from;
    u8 to;
    u8 pad_02[2];
    s32 elapsed;
    s32 duration;
} ScreenFade;

typedef struct {
    u8 pad_00000[0x18f2c];
    ScreenFade fade;
} StageManager;

extern StageActor *GetStageActor(int id);
extern void *GetStageObjectHandle(u16 id);
extern StageManager *func_ov001_0209c3e8(void);
extern u32 PlayStageSoundAt(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);
extern void func_ov001_02093358(GateRecord *record);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern void ScheduleSpawnerNextTime(GateRecord *record, fx32 delay);

int RunGateFadeSequence(GateRecord *record)
{
    StageActor *actor = GetStageActor(record->actorId);
    StageManager *manager;
    int mode;

    GetStageObjectHandle(record->objectId);
    manager = func_ov001_0209c3e8();
    if (record->armed && record->kind == 4) {
        switch (record->step) {
        case 0:
            if (actor != 0) {
                PlayStageSoundAt(0, 0x2f, &actor->position, 0);
            }
            manager->fade.from = 0;
            manager->fade.to = 0x10;
            manager->fade.elapsed = 0;
            manager->fade.duration = 0xa000;
            record->step++;
            break;
        case 1:
            if (manager->fade.duration == 0) {
                record->area = record->nextArea;
                func_ov001_02093358(record);
                manager->fade.from = 0x10;
                manager->fade.to = 0;
                manager->fade.elapsed = 0;
                manager->fade.duration = 0xa000;
                record->step++;
            }
            break;
        case 2:
            if (manager->fade.duration == 0) {
                record->step = 0;
                return 3;
            }
            break;
        }
    } else {
        if (func_ov001_02063a24()) {
            mode = func_ov001_02063a38();
        } else {
            mode = 0;
        }
        if (mode == 6) {
            ScheduleSpawnerNextTime(record, 0x96000);
        }
        return 3;
    }
    return 0;
}
