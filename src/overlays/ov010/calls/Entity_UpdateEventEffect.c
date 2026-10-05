#include "nitro/types.h"

typedef struct EventEffect {
    int state;
    int timer;
} EventEffect;

typedef struct Entity {
    u8 pad_000[0x9ac];
    u64 stateFlags;
    u8 pad_9b4[0x9c0 - 0x9b4];
    int delay;
} Entity;

extern EventEffect *data_ov010_020a1de0;

extern void UpdateObjectEffects(EventEffect *effect);
extern void UpdateTargetEffect(EventEffect *effect, int step);
extern BOOL func_ov001_020645c8(u32 eventId);
extern void ClearSessionPackedBit(int eventId);
extern void StartObjectEffects(EventEffect *effect);
extern void func_ov010_020a0d20(EventEffect *effect);
extern void SpawnEffectAtTarget(EventEffect *effect);
extern void Camera_ReturnFromPathView(void);

void Entity_UpdateEventEffect(Entity *entity, int step)
{
    EventEffect *effect = data_ov010_020a1de0;

    if (effect == NULL) {
        return;
    }
    UpdateObjectEffects(effect);
    UpdateTargetEffect(effect, step);
    if (func_ov001_020645c8(0x3713) && effect->state == 0) {
        if (entity->delay != 0x18) {
            effect->state = 1;
            effect->timer = 0;
            StartObjectEffects(effect);
        } else {
            ClearSessionPackedBit(0x3713);
        }
    }
    if (effect->state != 0) {
        effect->timer += step;
        if (effect->state == 1 && effect->timer >= 0x96000) {
            func_ov010_020a0d20(effect);
        }
        if (entity->stateFlags & 0x100000020ULL) {
            func_ov010_020a0d20(effect);
            SpawnEffectAtTarget(effect);
            Camera_ReturnFromPathView();
        }
    }
}
