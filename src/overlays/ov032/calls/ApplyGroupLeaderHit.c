#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupWorld {
    u8 pad_00[0x59];
    u8 kind;
} GroupWorld;

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    u8 pad_04[4];
    union {
        u32 raw;
        struct {
            u32 unk_08_0 : 15;
            u32 altSoundA : 1;
            u32 altSoundB : 1;
            u32 unk_08_17 : 15;
        } bits;
    } flags;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    GroupWorld *world;
    u8 pad_08[0x2b];
    u8 actorId;
    u8 pad_34[0x4];
    VecFx32 position;
    u8 pad_44[0x32];
    s8 countsDown;
    u8 pad_77[0x48];
    s8 hitLevel;
} GroupObject;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 unk_00_18 : 14;
    u32 mode : 4;
    u32 unk_04_4 : 4;
    u32 stunTimer : 8;
    u32 unk_04_16 : 16;
    union {
        u32 raw;
        struct {
            u32 needsRebuild : 1;
            u32 needsRefresh : 1;
            u32 unk_08_2 : 3;
            u32 dirty : 1;
            u32 flashTimer : 10;
            u32 unk_08_16 : 6;
            u32 lockTimer : 10;
        } bits;
    } state;
    u8 pad_0c[0x10];
    s32 maxHitPoints;
    s32 hitPoints;
} ObjectGroup;

typedef struct AttackInfo {
    u8 pad_00[0x28];
    u16 unk_28_0 : 1;
    u16 isHeavy : 1;
    u16 unk_28_2 : 14;
    u8 pad_2a[0x1a];
    u32 blocked : 1;
    u32 unk_44_1 : 31;
} AttackInfo;

typedef struct PartySlot {
    u16 unk_00;
    u16 attackerId;
} PartySlot;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern BOOL func_ov032_020bf0a8(GroupWorld *world, int groupIndex);
extern PartySlot *func_ov001_0209c1fc(u32 slot);
extern s32 ForwardToActiveServiceInstance(u32 attackerId, AttackInfo *attack, u32 flags);
extern void EnterFieldUnitPhase5(GroupObject *object, BOOL doReset);
extern int Fx32ToIntTruncate(int value);
extern void SpawnSoundSlot(int bank, int id, VecFx32 *position, int flags);
extern void func_ov001_02088204(u32 slotIndex, u8 kind, u8 subKind, s32 hitPoints, s32 maxHitPoints, const VecFx32 *position);
extern void HitAllGroupMembersExcept(GroupWorld *world, int groupIndex, GroupObject *object);
extern void func_ov001_02063a80(int index, int amount);
extern void HandleEnemyDefeat(s32 group, s32 index, VecFx32 *position, BOOL notify, int level);

void ApplyGroupLeaderHit(GroupObject *object, AttackInfo *attack)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    GroupMemberWork *work = func_ov032_020bbc98(object);
    BOOL defeated;
    BOOL locked;
    int sound;

    if (object->actorId == group->leaderIndex) {
        defeated = FALSE;
        if (attack != NULL) {
            if ((group->stunTimer == 0 || object->hitLevel == 0) &&
                !func_ov032_020bf0a8(object->world, work->groupIndex)) {
                group->hitPoints -= ForwardToActiveServiceInstance(func_ov001_0209c1fc(work->groupIndex)->attackerId, attack, 0);
                if (group->hitPoints < 0x1000) {
                    object->hitLevel = 0;
                    group->hitPoints = 0;
                    defeated = TRUE;
                    EnterFieldUnitPhase5(object, TRUE);
                }
                object->hitLevel = Fx32ToIntTruncate(group->hitPoints);
                if (group->state.bits.lockTimer == 0) {
                    group->state.bits.flashTimer = 20;
                }
                group->stunTimer = 10;
                if (attack->isHeavy) {
                    sound = work->flags.bits.altSoundA ? 3 : 2;
                    work->flags.bits.altSoundA = !work->flags.bits.altSoundA;
                } else {
                    sound = work->flags.bits.altSoundB ? 3 : 2;
                    work->flags.bits.altSoundB = !work->flags.bits.altSoundB;
                }
                if (sound != -1) {
                    SpawnSoundSlot(0xf8, sound, &object->position, 0);
                }
            } else if (func_ov032_020bf0a8(object->world, work->groupIndex)) {
                attack->blocked = 1;
            }
        }
        if (defeated) {
            func_ov001_02088204(work->groupIndex, object->world->kind, object->actorId, 0, group->maxHitPoints << 3,
                                &object->position);
            HitAllGroupMembersExcept(object->world, work->groupIndex, object);
            func_ov001_02063a80(0x1b, 1);
            func_ov001_02063a80(0x13, 1);
            HandleEnemyDefeat(-1, -1, &object->position, FALSE, -1);
        }
    } else {
        if (func_ov032_020bf0a8(object->world, work->groupIndex)) {
            return;
        }
        if (!group->state.bits.dirty) {
            locked = FALSE;
            if (group->state.bits.needsRefresh) {
                locked = TRUE;
            }
            if (!locked && object->countsDown != 0) {
                object->hitLevel--;
            }
            group->state.raw |= 0x20;
        }
    }
    work->flags.raw |= 8;
}
