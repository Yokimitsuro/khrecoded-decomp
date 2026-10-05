#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u16 actorId;
} StageController;

typedef struct {
    u8 pad_000[0x28c];
    u16 pad_bits0 : 7;
    u16 linkState : 4;
    u16 pad_bits1 : 5;
} StageActor;

typedef struct {
    u8 pad_00[6];
    u16 pad_bits0 : 9;
    u16 locked : 1;
    u16 pad_bits1 : 6;
    u8 pad_08[6];
    u16 kind;
    u16 active;
    u8 pad_12[0x50];
    u8 visible;
} StageEventRecord;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 scale;
    u8 pad_10[0x18];
    u16 flags;
    u8 pad_2a[0x1e];
} EventUpdateParams;

extern StageController *GetStageController(u32 id);
extern StageActor *GetStageActor(int id);
extern StageEventRecord *GetStageEventRecord(u32 id);
extern int ReleaseStageSlotEntry(int index, int slot);
extern u32 func_ov001_020877d0(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_ov001_0209591c(StageEventRecord *record, EventUpdateParams *params);

void ResetStageEntries(u32 mask)
{
    u16 i;

    if (mask & 1) {
        for (i = 0; i < 0x40; i++) {
            StageController *controller = GetStageController((u16)(i + 1));
            StageActor *actor;
            if (controller == 0 || controller->actorId == 0) {
                continue;
            }
            actor = GetStageActor((s16)controller->actorId);
            if (actor == 0 || actor->linkState == 0) {
                continue;
            }
            ReleaseStageSlotEntry(4, (u16)(i + 1));
        }
    }
    if (mask & 2) {
        u32 manager = func_ov001_020877d0();
        EventUpdateParams params;
        for (i = 0; i < *(u16 *)(manager + 0x18de4); i++) {
            StageEventRecord *record = GetStageEventRecord((u16)(i + 1));
            if (record == 0 || record->active == 0) {
                continue;
            }
            if (record->kind == 99 && record->locked) {
                continue;
            }
            if (record->visible == 0) {
                continue;
            }
            MI_CpuFill8(&params, 0, sizeof(params));
            params.scale = 0x64000;
            params.x = 0;
            params.y = 0;
            params.z = 0;
            params.flags |= 0x200;
            func_ov001_0209591c(record, &params);
        }
    }
}
