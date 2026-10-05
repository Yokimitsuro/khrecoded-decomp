#include "nitro/types.h"

typedef struct Entity Entity;

typedef int (*EntityModeFunc)(Entity *entity, int mode);
typedef void (*EntityChargeFunc)(Entity *entity, int amount);

struct Entity {
    u8 pad_000[0x1fc];
    EntityChargeFunc chargeCallback;
    u8 pad_200[0x234 - 0x200];
    u32 attributes;
    u8 pad_238[0x75c - 0x238];
    int actionKind;
    u8 pad_760[0x768 - 0x760];
    void *chargeTarget;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 pad_9b4[0x9c4 - 0x9b4];
    int chargeLevel;
    u8 pad_9c8[0x10ec - 0x9c8];
    EntityModeFunc modeCallback;
};

extern void *data_ov010_020a1de0;

extern void func_ov010_020a0cf8(void *actor);
extern void func_ov010_020a0d20(void *actor);

void Entity_UpdateSpecialCharge(Entity *entity)
{
    void *actor = data_ov010_020a1de0;

    if (entity->attributes & 4) {
        if (entity->modeCallback(entity, 0x1e) == 0x1e) {
            func_ov010_020a0cf8(actor);
        }
        return;
    }
    if (entity->chargeTarget != NULL && entity->actionKind == 0xc && entity->chargeCallback != NULL) {
        entity->chargeCallback(entity, 0xf000);
    }
    if (entity->chargeLevel >= 0x1e000) {
        func_ov010_020a0d20(actor);
        entity->stateFlags &= ~0x01000000ULL;
        entity->modeCallback(entity, 4);
    }
}
