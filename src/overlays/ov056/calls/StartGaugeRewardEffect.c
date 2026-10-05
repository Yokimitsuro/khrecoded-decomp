#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EntryInfo EntryInfo;
typedef void (*EntrySpawnCallback)(EntryInfo *info, s32 value, s32 arg2, s32 arg3);

struct EntryInfo {
    u8 pad_00[0x94];
    u16 facing;
    u8 pad_96[0xbc - 0x96];
    VecFx32 position;
    u8 pad_c8[0x1f0 - 0xc8];
    EntrySpawnCallback onSpawn;
};

typedef struct {
    u8 pad_00[4];
    u8 kind;
    u8 subKind;
    u8 pad_06[2];
    s32 power;
} RewardRequest;

typedef struct {
    u16 flags;
    u8 pad_02[0x7a];
    u16 rotY;
    u8 pad_7e[0x26];
    VecFx32 position;
    VecFx32 scale;
} RewardModel;

typedef struct {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[2];
    s8 activeCount;
    s8 flags;
    u8 pad_041[3];
    RewardModel model;
    u8 pad_100[0x50];
    u8 tracks[0x34];
    fx32 baseScale;
    s16 value;
    u8 pad_18a[2];
    s32 state;
    s32 timer;
    s32 duration;
    s32 pending;
    u8 kind;
    u8 subKind;
    u8 pad_19e[2];
    s32 power;
} RewardEffect;

extern EntryInfo *func_ov001_0206db5c(int index);
extern void func_ov021_020aef84(RewardModel *model, void *blendTable, int blendIndex);

void StartGaugeRewardEffect(RewardEffect *effect, void *arg, RewardRequest *request)
{
    EntryInfo *info;
    VecFx32 pos;
    u16 angle;
    fx32 scale;
    EntrySpawnCallback onSpawn;
    s32 value;

    info = func_ov001_0206db5c(effect->entryIndex);
    effect->flags = 0;
    angle = info->facing - 0x8000;
    pos = info->position;
    pos.y += 0x119a;
    func_ov021_020aef84(&effect->model, effect->tracks, 0);
    effect->model.position = pos;
    effect->model.rotY = angle + 0x8000;
    effect->model.flags |= 0x20;
    scale = effect->baseScale;
    effect->model.scale.z = scale;
    effect->model.scale.y = scale;
    effect->model.scale.x = scale;
    effect->flags |= 1;
    value = effect->value;
    onSpawn = info->onSpawn;
    if (onSpawn != NULL) {
        onSpawn(info, value, 0, 0);
    }
    effect->state = 1;
    effect->timer = 0;
    effect->pending = 1;
    effect->kind = request->kind;
    effect->subKind = request->subKind;
    effect->power = request->power;
    effect->activeCount++;
}
