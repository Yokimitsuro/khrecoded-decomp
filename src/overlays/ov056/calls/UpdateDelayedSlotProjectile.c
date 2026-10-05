#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EntryInfo {
    u8 pad_000[0xbc];
    VecFx32 position;
} EntryInfo;

typedef struct EffectSlotOwner {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[0xe8 - 0x3d];
    VecFx32 origin;
    u8 pad_0f4[0x198 - 0xf4];
    int fireTime;
    int elapsed;
    int slot;
    int kind;
    int subKind;
    int power;
    int phase;
} EffectSlotOwner;

extern void func_ov021_020aeba4(EffectSlotOwner *group, s32 step);
extern EntryInfo *func_ov001_0206db5c(int index);
extern void func_ov056_020d6920(EffectSlotOwner *unit, int slot, s32 kind, s32 subKind, s32 power);

void UpdateDelayedSlotProjectile(EffectSlotOwner *owner, s32 step)
{
    func_ov021_020aeba4(owner, step);
    owner->origin = func_ov001_0206db5c(owner->entryIndex)->position;
    if (owner->phase != 0) {
        if (owner->phase != 1) {
            owner->phase = 0;
            return;
        }
        owner->elapsed += step;
        if (owner->elapsed >= owner->fireTime) {
            func_ov056_020d6920(owner, owner->slot, owner->kind, owner->subKind, owner->power);
            owner->phase = 0;
        }
    }
}
