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

extern int func_ov018_020a37e4(u32 kind);
extern int func_ov001_02087d18(u16 id);
extern void func_ov001_02087988(u16 id, EventTargetInfo *info);
extern void func_ov001_02063a80(int counter, int value);
extern void SpawnRewardOrbs(u16 *amounts, VecFx32 *pos, u32 arg);
extern void func_ov059_020cf0c4(VecFx32 *out, RewardSource *src);

void SpawnSourceRewardOrbs(RewardSource *src, int multiplier, int counter) {
    EventTargetInfo info;
    int amount;

    switch (src->type) {
    case 1:
        amount = func_ov018_020a37e4(src->id.kind);
        break;
    case 2:
        amount = func_ov001_02087d18(src->id.eventId);
        func_ov001_02087988(src->id.eventId, &info);
        if (info.isPartner) {
            func_ov001_02063a80(counter, amount);
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
        func_ov059_020cf0c4(&pos, src);
        SpawnRewardOrbs(amounts, &pos, 0);
    }
}
