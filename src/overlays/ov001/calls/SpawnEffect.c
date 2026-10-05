#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TextureParams {
    u32 imageParam;
    u32 paletteParam;
} TextureParams;

typedef struct EffectTask {
    u8 pad_00[0x10];
    void *activeList;
} EffectTask;

typedef struct Effect {
    u8 pad_00[8];
    TextureParams *texture;
    VecFx32 drawPos;
    s16 width;
    s16 height;
    u8 unk_1C;
    u8 unk_1D;
    s8 unk_1E;
    s8 unk_1F;
    s16 alpha;
    s16 angle;
    EffectTask *task;
    int variant;
    u8 type;
    u8 slot;
    s8 palette : 4;
    s8 spinDirection : 4;
    u8 orbitsOrigin : 1;
    u8 unk_2F_1 : 1;
    u8 unk_2F_2 : 1;
    u8 unk_2F_3 : 1;
    u8 unk_2F_4 : 1;
    u8 unk_2F_5 : 1;
    s16 startAngle;
    s16 lifetime;
    int size;
    VecFx32 pos;
    VecFx32 velocity;
    int age;
} Effect;

typedef struct EffectHost {
    int *usedBits;
    TextureParams textures[7];
    EffectTask task;
    u8 pad_50[0x1be];
    s8 angleCounter;
    u8 suspended : 1;
    u8 suspendPending : 1;
    u8 pad_210[4];
    Effect effects[1];
} EffectHost;

extern s8 data_ov001_0209d9b4[][4];
extern EffectHost *data_ov001_020a0484;
extern void ClearPackedBit(int *bitWords, int bitIndex);
extern unsigned int func_0202a9e4(unsigned int range);
extern int func_020367c4(EffectTask *task, Effect *effect);
extern void ActorSlot_LinkAsRoot(EffectTask *task);
extern s32 func_ov001_02063a38(void);
extern int func_ov001_02064a38(int *command, int flag);
extern void func_ov001_02072254(int *command, int flag);
extern void SetNodeStateRandomDir(Effect *effect, int palette);

Effect *SpawnEffect(int slot, int type, int variant, VecFx32 *pos, int motionType)
{
    s8 *entry = data_ov001_0209d9b4[type];
    Effect *effect;

    ClearPackedBit(data_ov001_020a0484->usedBits, slot);
    effect = &data_ov001_020a0484->effects[slot];
    effect->task = &data_ov001_020a0484->task;
    effect->palette = 0xf;
    effect->type = type;
    effect->slot = slot;
    effect->variant = variant;
    effect->orbitsOrigin = (motionType == 3);
    effect->unk_2F_1 = (motionType == 4);
    effect->unk_2F_3 = (motionType == 5);
    effect->unk_2F_4 = 0;
    effect->lifetime = 0x30;
    effect->pos = *pos;
    effect->age = 0;
    if (type == 6 && func_ov001_02064a38(&variant, 0) == 0) {
        effect->unk_2F_2 = 1;
        effect->unk_2F_1 = 1;
        func_ov001_02072254(&variant, 0);
    }
    effect->unk_2F_5 = effect->unk_2F_3 | effect->unk_2F_1;

    if (type >= 6) {
        effect->size = 0x500;
    } else if (type == 1) {
        switch (variant) {
        case 0:
            effect->size = 0x1c0;
            break;
        case 1:
            effect->size = 0x280;
            break;
        default:
            effect->size = 0x400;
            break;
        }
    } else {
        switch (variant) {
        case 0:
            effect->size = 0x200;
            break;
        case 1:
            effect->size = 0x400;
            break;
        default:
            effect->size = 0x500;
            break;
        }
    }

    switch (motionType) {
    case 0:
    case 4:
    case 5:
        effect->velocity.x = func_0202a9e4(0x260) - 0x130;
        effect->velocity.y = func_0202a9e4(0x1c0) + 0x340;
        effect->velocity.z = func_0202a9e4(0x260) - 0x130;
        break;
    case 1:
        effect->velocity.x = 0;
        effect->velocity.y = 0x200;
        effect->velocity.z = 0;
        break;
    case 2:
    case 3:
        effect->velocity.x = 0;
        effect->velocity.y = 0;
        effect->velocity.z = 0;
        break;
    case 6:
        effect->velocity.x = func_0202a9e4(0x5f0) - 0x2f8;
        effect->velocity.y = func_0202a9e4(0x540) + 0x4e0;
        effect->velocity.z = func_0202a9e4(0x5f0) - 0x2f8;
        effect->lifetime += effect->lifetime >> 1;
        break;
    }
    effect->lifetime /= 2;

    if (func_ov001_02063a38() == 4) {
        effect->velocity.z = 0;
    }
    if (effect->task != NULL && effect->task->activeList == NULL) {
        ActorSlot_LinkAsRoot(effect->task);
    }
    effect->texture = &data_ov001_020a0484->textures[entry[0]];
    effect->drawPos = effect->pos;
    if (effect->orbitsOrigin) {
        effect->velocity = effect->pos;
        effect->startAngle = data_ov001_020a0484->angleCounter << 14;
        data_ov001_020a0484->angleCounter = (data_ov001_020a0484->angleCounter + 1) & 3;
    }
    effect->height = effect->size << 1;
    effect->width = effect->height;
    effect->unk_1D = 0;
    effect->unk_1C = effect->unk_1D;
    effect->unk_1E = entry[1];
    effect->unk_1F = entry[2];
    effect->alpha = 0x1f;
    effect->angle = 0;
    if (effect->task != NULL) {
        func_020367c4(effect->task, effect);
    }
    if (data_ov001_020a0484->suspendPending) {
        SetNodeStateRandomDir(effect, 0);
    }
    return effect;
}
