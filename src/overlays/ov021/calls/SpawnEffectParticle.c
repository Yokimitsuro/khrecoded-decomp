#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PartyEntry {
    u8 pad_000[0x94];
    u16 yaw;
    u8 pad_096[0x26];
    VecFx32 position;
    u8 pad_0c8[0x160];
    BOOL (*getTarget)(struct PartyEntry *entry, VecFx32 *out);
} PartyEntry;

typedef struct {
    s8 stage;
    u8 pad_01[3];
    fx32 time;
    u16 yaw;
    u8 pad_0a[2];
    VecFx32 position;
    u8 colorA;
    u8 colorB;
    u8 pad_1a[2];
    u32 param;
    void *slot;
} EffectParticle;

typedef struct {
    u8 pad_00[4];
    u8 colorA;
    u8 colorB;
    u8 pad_06[2];
    u32 param;
} ParticleDesc;

typedef struct {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d;
    s8 particleCount;
    s8 activeParticles;
    s8 flags;
    u8 pad_041[0x14b];
    EffectParticle *particles;
} EffectSystem;

extern PartyEntry *GetBoundedEntryField(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern int FX_Atan2Idx(fx32 y, fx32 x);
extern VecFx32 func_ov021_020aed44(EffectSystem *system, int slot);

void SpawnEffectParticle(EffectSystem *system, int slot, ParticleDesc *desc) {
    PartyEntry *entry = GetBoundedEntryField(system->entryIndex);
    u16 facing = (u16)(entry->yaw - 0x8000);
    u16 yaw = facing + 0x8000;
    EffectParticle *particle = NULL;
    int i;
    VecFx32 origin;
    VecFx32 diff;
    VecFx32 target;
    BOOL hasTarget;
    for (i = 0; i < system->particleCount; i++) {
        if (system->particles[i].stage < 0) {
            particle = &system->particles[i];
            break;
        }
    }
    if (particle == NULL) {
        system->flags &= ~1;
        return;
    }
    origin = entry->position;
    if (entry->getTarget != NULL) {
        hasTarget = entry->getTarget(entry, &target);
    } else {
        hasTarget = FALSE;
    }
    if (hasTarget) {
        VEC_Subtract(&target, &origin, &diff);
        yaw = FX_Atan2Idx(diff.x, diff.z);
    }
    particle->position = origin;
    particle->yaw = yaw;
    particle->position.y += 0x800;
    particle->stage = 0;
    particle->time = 0;
    particle->slot = NULL;
    particle->colorA = desc->colorA;
    particle->colorB = desc->colorB;
    particle->param = desc->param;
    system->activeParticles++;
    func_ov021_020aed44(system, slot);
}
