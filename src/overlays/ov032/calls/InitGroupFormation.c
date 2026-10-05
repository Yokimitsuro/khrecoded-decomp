#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
    u8 pad_08[0x2A];
    u8 actorId;
} GroupObject;

typedef struct GroupMotion {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} GroupMotion;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 unk_00_18 : 14;
    u32 unk_04;
    u32 unk_08_0 : 4;
    u32 isAnchored : 1;
    u32 unk_08_5 : 27;
    u16 memberCount : 8;
    u16 unk_0C_8 : 8;
    u8 pad_0E[0x16];
    s32 unk_24;
    u8 pad_28[0x10];
    VecFx32 memberOffsets[20];
    VecFx32 center;
    VecFx32 velocity;
    GroupMotion motion;
} ObjectGroup;

extern const VecFx32 data_0205344c;
extern const GroupMotion data_0205584c;
extern const s16 data_02053580[];

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern void *ActorRegistry_GetEntityByIndex(int actorId);
extern u8 *func_ov001_02086384(void *world, int index);
extern BOOL IsFieldUnitPhase6(u8 *member);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void DivideVecFx32ByScalar(VecFx32 *vec, s32 divisor);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern int GetRemainingRowSpan(u8 *leader);
extern u32 random_next_scaled(u32 upperBound);

extern s64 _ll_mul(s64 a, s64 b);

#define FX_MUL_ROUND(a, b) ((fx32)((_ll_mul((a), (b)) + 0x800) >> 12))

void InitGroupFormation(GroupObject *object)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    u8 *leader;
    VecFx32 zeroVec;
    VecFx32 sum;
    VecFx32 anchor;
    s32 slots[64];
    int count;
    int i;
    int remaining;

    ActorRegistry_GetEntityByIndex(object->actorId);
    leader = func_ov001_02086384(object->world, group->leaderIndex);
    zeroVec = data_0205344c;
    sum = data_0205344c;
    count = 0;
    if (!group->isAnchored) {
        for (i = count; i < group->memberCount; i++) {
            u8 *member = func_ov001_02086384(object->world, group->firstMember + i);
            if (IsFieldUnitPhase6(member) == 0) {
                VEC_Add((VecFx32 *)(member + 0x38), &sum, &sum);
                count++;
            }
        }
        DivideVecFx32ByScalar(&sum, count);
        group->center = sum;
    } else {
        anchor = *func_ov001_0206dc4c(count);
        anchor.y += 0x5000;
        anchor.y = anchor.y > 0xc000 ? 0xc000 : anchor.y;
        group->center = anchor;
    }
    for (remaining = 0; remaining < 64; remaining++) {
        slots[remaining] = remaining;
    }
    for (i = 0; i < group->memberCount; i++) {
        VecFx32 *offset = &group->memberOffsets[i];
        if (i != GetRemainingRowSpan(leader)) {
            int pick = random_next_scaled(remaining);
            s32 slot = slots[pick];
            s32 column = slot % 8;
            s32 row = slot / 8;
            int j;
            s32 latIndex;
            s32 lonIndex;

            for (j = pick; j < remaining - 1; j++) {
                slots[pick] = slots[pick + 1];
            }
            lonIndex = ((row << 16) / 8) >> 4;
            latIndex = ((column << 15) / 8) >> 4;
            remaining--;
            offset->x = FX_MUL_ROUND(FX_MUL_ROUND(data_02053580[latIndex], data_02053580[(0x400 - lonIndex) & 0xfff]), 0x1b33);
            offset->y = FX_MUL_ROUND(data_02053580[(0x400 - latIndex) & 0xfff], 0x1b33);
            offset->z = FX_MUL_ROUND(FX_MUL_ROUND(data_02053580[latIndex], data_02053580[lonIndex]), 0x1b33);
        } else {
            *offset = zeroVec;
        }
    }
    group->unk_24 = 0;
    group->motion = data_0205584c;
}
