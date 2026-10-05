#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xbc];
    VecFx32 position;
} EntryInfo;

typedef struct RewardEffect RewardEffect;
typedef void (*RewardCallback)(RewardEffect *effect, s32 ownerId);

struct RewardEffect {
    s32 ownerId;
    u8 pad_004[0x38];
    s8 entryIndex;
    u8 pad_03d[2];
    s8 activeCount;
    u8 pad_040[0xa8];
    VecFx32 position;
    u8 pad_0f4[0x17c - 0xf4];
    s32 basePoints;
    u8 pad_180[0xc];
    s32 state;
    s32 timer;
    s32 duration;
    s32 pending;
    s8 bonusPercent;
    s8 flags;
    u8 pad_19e[6];
    RewardCallback onReward;
};

extern EntryInfo *GetBoundedEntryField(int index);
extern void AwardPartyGaugePoints(s32 ownerId, s32 points);
extern BOOL StepEffectAnimation(RewardEffect *effect, s32 step);

void UpdateGaugeRewardEffect(RewardEffect *effect, s32 step)
{
    EntryInfo *info = GetBoundedEntryField(effect->entryIndex);
    VecFx32 pos;
    s32 points;

    if (effect->state == 0) {
        return;
    }
    effect->timer += step;
    switch (effect->state) {
    case 1:
        pos = info->position;
        pos.y += 0x119a;
        effect->position = pos;
        if (effect->timer >= effect->duration && effect->pending != 0) {
            effect->onReward(effect, effect->ownerId);
            effect->pending = 0;
            points = effect->basePoints;
            if (effect->flags & 1) {
                points += points * effect->bonusPercent / 100;
            }
            AwardPartyGaugePoints(effect->ownerId, points >> 12);
        }
        if (StepEffectAnimation(effect, step)) {
            effect->timer = 0;
            effect->state = 3;
        }
        break;
    case 3:
        effect->state = 0;
        effect->activeCount--;
        break;
    }
}
