#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventTargetInfo {
    u16 id;
    u16 isPartner : 1;
    u16 rest : 15;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct RewardSource {
    union {
        u32 kind;
        u16 eventId;
    } id;
    int type;
} RewardSource;

extern int GetKindDuration(u32 kind);
extern int StageRecord_GetLinkedEntryValue(u16 id);
extern void func_ov001_02087988(u16 id, EventTargetInfo *info);
extern void AddSessionCounter(int counter, int value);
extern void SpawnRewardOrbs(u16 *amounts, VecFx32 *pos, u32 arg);
extern void TargetKey_GetPosition(VecFx32 *out, RewardSource *src);

void SpawnSourceRewardOrbs(RewardSource *src, int multiplier, int counter) {
    EventTargetInfo info;
    int amount;

    switch (src->type) {
    case 1:
        amount = GetKindDuration(src->id.kind);
        break;
    case 2:
        amount = StageRecord_GetLinkedEntryValue(src->id.eventId);
        func_ov001_02087988(src->id.eventId, &info);
        if (info.isPartner) {
            AddSessionCounter(counter, amount);
            return;
        }
        break;
    }
    if (multiplier >= 2) {
        amount = amount * multiplier;
    }
    if (amount != 0) {
        u16 amounts[6] = {0, 0, 0, 0, 0, 0};
        VecFx32 pos;
        amounts[2] = amount / 10;
        TargetKey_GetPosition(&pos, src);
        SpawnRewardOrbs(amounts, &pos, 0);
    }
}
