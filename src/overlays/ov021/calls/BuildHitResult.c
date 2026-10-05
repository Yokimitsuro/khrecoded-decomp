#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u32 unk_04;
    u32 kind;
    VecFx32 position;
    void *node;
    u32 data[0x2e];
} HitResult;

typedef struct {
    fx32 scale;
    VecFx32 direction;
} HitContact;

typedef struct {
    u8 pad_00[0xc];
    u8 attackType;
    u8 unk_0d;
    u8 pad_0e[2];
    u32 element;
    u32 power;
    u32 bonus;
} HitInfo;

typedef struct {
    u8 pad_00[4];
    fx32 damage;
    u8 pad_08[8];
    u8 power;
    u8 bonus;
    u8 pad_12[0x12];
    u16 flagsLow : 4;
    u16 attacking : 1;
    u16 flags5 : 3;
    u16 noReward : 1;
    u16 flagsHigh : 7;
    u8 element;
} HitOptions;

extern void func_ov021_020ac168(HitResult *result);
extern void ComputeKnockbackVector(HitInfo *info, void *attack, HitOptions *options, void *data);
extern u32 func_ov001_02086408(void *node, HitInfo *info);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void AwardPartyGaugePoints(int index, int points);
extern BOOL IsObjectIdle(HitOptions *options);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern VecFx32 GetShapeCenter(const void *shape);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

HitResult BuildHitResult(int owner, void *attack, HitOptions *options, HitContact *contact, u8 *node) {
    HitInfo info;
    VecFx32 offset;
    HitResult result;
    func_ov021_020ac168(&result);
    if (options != NULL) {
        int attacking;
        ComputeKnockbackVector(&info, attack, options, node + 0x38);
        info.attackType = owner;
        info.unk_0d = 0;
        info.element = options->element;
        info.power = options->power;
        info.bonus = options->bonus;
        if (!options->noReward) {
            result.flags = func_ov001_02086408(node, &info);
            if (!(result.flags & 1)) {
                AwardPartyGaugePoints(owner, FX_Mul(options->damage, 0x1000) >> 12);
            }
        }
        result.flags |= 0x80;
        attacking = options->attacking;
        options->attacking = 0;
        if (!IsObjectIdle(options)) {
            result.flags &= ~1;
        }
        options->attacking = attacking;
    }
    result.kind = 3;
    result.node = node;
    func_01ffafb4(contact->scale - 0x59a, &contact->direction, &offset);
    {
        VecFx32 center = GetShapeCenter(attack);
        VEC_Add(&center, &offset, &result.position);
    }
    return result;
}
