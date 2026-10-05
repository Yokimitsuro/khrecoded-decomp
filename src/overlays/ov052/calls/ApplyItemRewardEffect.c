#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 player;
    u8 pad_01[7];
    fx32 rate;
    u8 pad_0c[0x24 - 0x0c];
    u8 critical;
    u8 visible;
    u8 pad_26[2];
    s16 effectId;
    s16 delay;
} RewardEffect;

typedef struct {
    u8 pad_0[2];
    u16 health;
} MemberStats;

typedef struct PartyMember PartyMember;

struct PartyMember {
    u8 pad_000[0x1d4];
    MemberStats *stats;
    u8 pad_1d8[0x200 - 0x1d8];
    void (*revive)(PartyMember *member, int arg);
};

typedef struct RewardActor RewardActor;

struct RewardActor {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x22c - 0x1e0];
    int (*getState)(RewardActor *actor);
    u8 pad_230[0x9ac - 0x230];
    u64 stateFlags;
    u8 player;
    u8 pad_9b5[0x1035 - 0x9b5];
    s8 healTarget;
};

extern void ResetAnimationTrackState(RewardEffect *effect);
extern int func_ov021_020a8cc0(RewardEffect *effect, int groupId);
extern void AddSessionCounter(int index, int amount);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern int func_ov001_0206dc38(void);
extern PartyMember *GetBoundedEntryField(int index);
extern BOOL AddClampedHealth(PartyMember *member, int delta);
extern void func_ov040_020bda8c(int entry, int amount);
extern BOOL func_ov001_0206e224(void);
extern void AwardPartyGaugePoints(int index, int points);
extern void AdvanceMenuLevel(int step);
extern s32 func_ov001_02078494(void);
extern void func_ov001_02078360(int mode, int arg);
extern void func_ov001_02078000(int listKind, int entryId);
extern void FieldMenu_TryOpenByMode(void);
extern u8 UpdateSelectionCount(int order);
extern BOOL func_ov001_0206e2d0(void);
extern int AddSlotItemUses(int order);
extern void func_ov001_020784a4(s32 id, s32 count);

void ApplyItemRewardEffect(RewardActor *actor, int groupId, int kind, int order, BOOL openMenu)
{
    int heal = 0;
    int gauge = 0;
    RewardEffect effect;
    int revive = 0;
    int i;
    int state;
    int count;
    int uses;

    ResetAnimationTrackState(&effect);
    effect.player = actor->player;
    effect.visible = 1;
    effect.critical = 0;
    effect.delay = 0;
    effect.rate = FX32_ONE;
    if (actor->stateFlags & 0x40) {
        effect.rate = 0xb33;
    }
    switch (kind) {
    case 0xb7:
        effect.effectId = 0xb2;
        heal = 0x1e;
        break;
    case 0xb8:
        effect.effectId = 0xb3;
        heal = 0x32;
        break;
    case 0xbb:
        effect.effectId = 0xb6;
        revive = 1;
        break;
    case 0xb9:
        effect.effectId = 0xb4;
        gauge = 1;
        break;
    case 0xba:
        effect.effectId = 0xb5;
        gauge = 2;
        break;
    case 0xbc:
        effect.effectId = 0xb7;
        heal = 1000;
        revive = 1;
        break;
    case 0xbd:
        effect.effectId = 0xb8;
        heal = 1000;
        gauge = 5;
        revive = 1;
        AddSessionCounter(0x12, 1);
        break;
    }
    if (IsPlayerEntryFlagSet(actor->player, 0x45)) {
        heal += (heal * FX32_ONE) >> FX32_SHIFT;
        gauge *= 2;
    }
    if (revive > 0) {
        for (i = 0; i < func_ov001_0206dc38(); i++) {
            PartyMember *member = GetBoundedEntryField(i);
            if (member->revive != NULL) {
                member->revive(member, 0);
            }
        }
    }
    if (heal > 0) {
        if (actor->healTarget == 0) {
            for (i = 0; i < func_ov001_0206dc38(); i++) {
                PartyMember *member = GetBoundedEntryField(i);
                if (member->stats->health != 0) {
                    AddClampedHealth(member, (s16)heal);
                }
            }
        } else {
            func_ov040_020bda8c(actor->healTarget, heal);
            actor->healTarget = 0;
        }
    }
    if (!func_ov001_0206e224()) {
        gauge = 0;
    }
    if (actor->getState != NULL) {
        state = actor->getState(actor);
    } else {
        state = actor->state;
    }
    if (state == 10) {
        gauge = 0;
    }
    if (gauge > 0) {
        AwardPartyGaugePoints(actor->player, 0);
        AdvanceMenuLevel(gauge);
    }
    if (groupId >= 0) {
        func_ov021_020a8cc0(&effect, groupId);
        for (i = 1; i < func_ov001_0206dc38(); i++) {
            PartyMember *member = GetBoundedEntryField(i);
            effect.player = i;
            if (member->stats->health != 0) {
                func_ov021_020a8cc0(&effect, groupId);
            }
        }
    }
    if (openMenu) {
        if (func_ov001_02078494() == 2) {
            func_ov001_02078360(0, 1);
        }
        func_ov001_02078000(func_ov001_02078494(), order);
        FieldMenu_TryOpenByMode();
    }
    count = UpdateSelectionCount(order);
    if (func_ov001_0206e2d0() && (uses = AddSlotItemUses(order)) > 0) {
        count = uses;
    }
    func_ov001_020784a4((u16)order, (u16)count);
}
