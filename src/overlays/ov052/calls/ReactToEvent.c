#include "nitro/types.h"

typedef struct Entity Entity;

typedef struct HitEvent {
    u8 pad_00[0x3C];
    s8 kind;
} HitEvent;

struct Entity {
    u8 pad_000[0x1F8];
    void (*onStateChanged)(Entity *entity, int state, int param);
    u8 pad_1FC[0x564];
    int power;
    u8 pad_764[0x250];
    u8 slotIndex;
    u8 pad_9B5[0x17];
    int cooldown;
    u8 pad_9D0[0x6A8];
    int *linkedObject;
    u8 pad_107C[0x70];
    void (*changeState)(Entity *entity, int state);
};

extern void *func_ov001_0206db78(int index);
extern BOOL func_ov021_020a7524(void *slot);
extern BOOL func_ov001_02072040(void);
extern BOOL func_ov052_020c8bcc(Entity *entity);
extern BOOL FindDashWallTarget(Entity *entity, HitEvent *event);
extern BOOL TryStartSpecialAction(Entity *entity);
extern BOOL SelectGroundAction(Entity *entity, HitEvent *event);
extern BOOL TryEnterLevelTargetState(Entity *entity, HitEvent *event);

BOOL ReactToEvent(Entity *entity, HitEvent *event)
{
    void *slot = func_ov001_0206db78(entity->slotIndex);
    BOOL handled = FALSE;

    switch (event->kind) {
    case 1:
    case 2:
        if (entity->cooldown <= 0) {
            if (func_ov052_020c8bcc(entity)) {
                entity->changeState(entity, 6);
                handled = TRUE;
            } else if (FindDashWallTarget(entity, event)) {
                entity->changeState(entity, 16);
                handled = TRUE;
            }
        }
        if (!handled) {
            handled = TryStartSpecialAction(entity);
        }
        if (!handled) {
            handled = TryEnterLevelTargetState(entity, event);
        }
        break;
    case 3:
        if (entity->power >= 0x4000) {
            handled = SelectGroundAction(entity, event);
            if (handled) {
                break;
            }
            if (entity->power >= 0x6000 && func_ov021_020a7524(slot)) {
                entity->changeState(entity, 1);
                if (entity->onStateChanged != NULL) {
                    entity->onStateChanged(entity, 1, -1);
                }
                handled = TRUE;
            }
        } else if (func_ov001_02072040() && entity->linkedObject != NULL && *entity->linkedObject == 0xC4) {
            handled = SelectGroundAction(entity, event);
        }
        break;
    }
    return handled;
}
