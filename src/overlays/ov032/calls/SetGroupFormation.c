#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u32 firstMember : 9;
    u32 unk_00_9 : 23;
    u32 formation : 4;
    u32 prevFormation : 4;
    u32 unk_04_8 : 8;
    u32 memberTotal : 8;
    u32 arrivedCount : 8;
    u32 unk_08;
    u16 memberCount : 8;
    u16 unk_0c_8 : 1;
    u16 turning : 1;
    u16 settled : 1;
    u16 unk_0c_11 : 5;
    u8 pad_0e[8];
    u16 unk_16;
    u8 pad_18[2];
    u16 unk_1a;
    u8 pad_1c[0x18];
    u32 unk_34;
    u8 pad_38[0x1a8];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

typedef struct {
    u8 pad_00[4];
    FieldContext *world;
} GroupObject;

typedef struct {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    u8 pad_04[4];
    u32 hopping : 1;
    u32 rising : 1;
    u32 facingFlip : 1;
    u32 unk_08_3 : 29;
    u8 pad_0c[4];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x18];
    s32 unk_30;
    MtxFx33 basis;
} GroupMemberWork;

extern const MtxFx33 data_02053458;
extern const VecFx32 data_0205344c;

extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern GroupObject *func_ov001_02086384(FieldContext *context, int index);
extern BOOL IsFieldUnitPhase6(GroupObject *object);
extern void func_ov032_020bbd80(GroupObject *object, const VecFx32 *dir);
extern void ScatterGroupAroundLeader(GroupObject *object);
extern void ScatterGroupMembers(GroupObject *object);
extern void ResetGroupMemberFlags(GroupObject *object);
extern void ResetGroupMemberPhases(GroupObject *object);
extern void InitGroupMode4(GroupObject *object);
extern void ScatterGroupMembers_020befdc(GroupObject *object);

void SetGroupFormation(GroupObject *object, u32 formation)
{
    FieldContext *world = object->world;
    GroupMemberWork *work = func_ov032_020bbc98(object);
    FieldObject *group = &world->objects[work->groupIndex];
    int i;

    for (i = 0; i < group->memberCount; i++) {
        GroupObject *member = func_ov001_02086384(world, group->firstMember + i);
        GroupMemberWork *memberWork = func_ov032_020bbc98(member);
        if (!IsFieldUnitPhase6(member)) {
            memberWork->hopping = 0;
            memberWork->rising = 0;
            memberWork->unk_14 = 0;
            memberWork->facingFlip = 0;
            memberWork->unk_10 = 0;
            memberWork->unk_30 = 0;
        }
        memberWork->basis = data_02053458;
        func_ov032_020bbd80(member, &data_0205344c);
    }
    switch (formation) {
    case 0:
        ScatterGroupAroundLeader(object);
        break;
    case 1:
        ScatterGroupMembers(object);
        break;
    case 2:
        ResetGroupMemberFlags(object);
        break;
    case 4:
        InitGroupMode4(object);
        break;
    case 3:
        ResetGroupMemberPhases(object);
        break;
    case 5:
        ScatterGroupMembers_020befdc(object);
        break;
    }
    group->turning = 0;
    group->settled = 0;
    group->unk_1a = 0;
    group->arrivedCount = 0;
    group->formation = formation;
    group->unk_16 = 0;
    group->prevFormation = group->formation;
    group->unk_34 = 0;
}
