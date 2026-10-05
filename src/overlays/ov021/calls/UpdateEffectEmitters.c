#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[2];
    s8 handler;
    u8 pad_03[0x151];
} EffectSlot;

typedef struct {
    s8 stage;
    u8 pad_01[3];
    fx32 time;
    u8 pad_08[0x18];
    EffectSlot *slot;
} EffectParticle;

typedef struct EffectSystem {
    u8 pad_00[8];
    EffectSlot *slots;
    u8 *context;
    u8 pad_10[5];
    u8 slotCount;
    u8 pad_16[0x12];
    void (*handlers[5])(struct EffectSystem *system, EffectSlot *slot, fx32 step);
    u8 pad_3c[2];
    s8 particleCount;
    s8 activeParticles;
    u8 pad_40[0x14c];
    EffectParticle *particles;
    u8 pad_190;
    s8 stageLimit;
    u8 pad_192[2];
    fx32 spawnTime;
} EffectSystem;

extern BOOL StepEffectAnimation(EffectSystem *system, fx32 step);
extern void SpawnPatternShot(EffectSystem *system, EffectParticle *particle, u32 arg);

void UpdateEffectEmitters(EffectSystem *system, fx32 step) {
    u8 *context = system->context;
    int i;
    for (i = 0; i < system->slotCount; i++) {
        EffectSlot *slot = &system->slots[i];
        if (slot->handler != -1) {
            system->handlers[slot->handler](system, slot, step);
        }
    }
    StepEffectAnimation(system, step);
    for (i = 0; i < system->particleCount; i++) {
        EffectParticle *particle = &system->particles[i];
        if (particle->stage >= 0) {
            particle->time += step;
            if (particle->stage < system->stageLimit && particle->time >= system->spawnTime) {
                SpawnPatternShot(system, particle, *(u32 *)(context + 0xc));
            }
        }
        if (particle->slot != NULL && particle->slot->handler == -1) {
            system->activeParticles--;
            particle->stage = -1;
            particle->slot = NULL;
        }
    }
}
