#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RewardEntry {
    u16 eventId;
    u16 subId;
    int type;
} RewardEntry;

typedef struct RewardQueue {
    u8 pad_000[0x60];
    RewardEntry entries[16];
    fx32 timers[8];
    fx32 fades[8];
    u8 count;
    u8 capacity;
} RewardQueue;

typedef struct EventTargetInfo {
    u16 id;
    u16 flags;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 hitPoints;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct AttackDesc {
    fx32 power;
    u8 pad_04[0xc];
    u8 attackType;
    u8 element;
    u8 pad_12[0x28 - 0x12];
} AttackDesc;

typedef struct HitInfo {
    VecFx32 direction;
    fx32 damage;
    u8 pad_10[0x2a - 0x10];
    u16 targetSubId;
    u8 pad_2c[2];
    u16 unk_2e;
    u16 attackerLevel;
    u8 pad_32[2];
    VecFx32 origin;
    u8 pad_40[0x48 - 0x40];
} HitInfo;

typedef struct PlayerStats {
    u8 pad_00;
    u8 level;
} PlayerStats;

typedef struct PlayerEntry {
    u8 pad_000[0x1d4];
    PlayerStats *stats;
} PlayerEntry;

extern const VecFx32 data_0205344c;
extern void func_ov001_02087988(u16 id, EventTargetInfo *info);
extern void ZeroBytes0x28(void *obj);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern PlayerEntry *GetBoundedEntryField(int player);
extern VecFx32 *func_ov001_0206dc4c(int player);
extern fx32 ComputeAttackDamage(int player, AttackDesc *attack);
extern s32 ForwardToActiveServiceInstance(u32 eventId, HitInfo *hit, u32 subId);

BOOL RewardQueue_CanAddEventHit(RewardQueue *queue, u16 eventId, u16 subId) {
    HitInfo hit;
    EventTargetInfo info;
    AttackDesc attack;
    u32 count = queue->count;
    u8 i = 0;
    u8 matches = 0;

    for (; i < count; i++) {
        if (queue->entries[i].type == 2 && eventId == queue->entries[i].eventId
            && subId == queue->entries[i].subId) {
            if (queue->fades[i] < 0x5000) {
                return FALSE;
            }
            matches++;
        }
    }
    if (matches == 0) {
        return TRUE;
    }
    func_ov001_02087988(eventId, &info);
    ZeroBytes0x28(&attack);
    attack.power = 0x1800;
    attack.attackType = 0;
    MI_CpuFill8(&hit, 0, sizeof(HitInfo));
    hit.unk_2e = 0;
    hit.attackerLevel = GetBoundedEntryField(0)->stats->level;
    hit.origin = *func_ov001_0206dc4c(0);
    hit.direction = data_0205344c;
    hit.targetSubId = subId;
    hit.damage = ComputeAttackDamage(0, &attack);
    {
        s32 damage = ForwardToActiveServiceInstance(eventId, &hit, subId);
        return damage * matches < info.hitPoints << 12;
    }
}
