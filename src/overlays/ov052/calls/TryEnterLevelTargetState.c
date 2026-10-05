#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Entity Entity;

typedef struct HitEvent {
    u8 pad_00[0x3C];
    s8 kind;
    u8 pad_3D;
    s8 source;
} HitEvent;

struct Entity {
    u8 pad_000[0x228];
    BOOL (*isTargetValid)(Entity *entity, int mode);
    u8 pad_22C[0xE1C];
    u8 target[4];
    u8 pad_104C[0xA0];
    void (*changeState)(Entity *entity, int state);
};

extern VecFx32 *GetWaitTargetPosition(void *target);
extern VecFx32 *func_ov052_020ceb74(Entity *entity);

BOOL TryEnterLevelTargetState(Entity *entity, HitEvent *event)
{
    BOOL triggered = FALSE;
    int valid;

    if (event->source != 1) {
        return FALSE;
    }
    if (entity->isTargetValid != NULL) {
        valid = entity->isTargetValid(entity, 0);
    } else {
        valid = 0;
    }
    if (valid != 0) {
        VecFx32 *targetPos = GetWaitTargetPosition(entity->target);
        VecFx32 *selfPos = func_ov052_020ceb74(entity);

        if (targetPos->y >= selfPos->y) {
            if (targetPos->y < selfPos->y + 0xC00) {
                triggered = TRUE;
            }
        } else if (targetPos->y > selfPos->y - 0xC00) {
            triggered = TRUE;
        }
    }
    if (event->kind == 2) {
        triggered = TRUE;
    }
    if (triggered) {
        entity->changeState(entity, 12);
    }
    return triggered;
}
