#include "nitro/types.h"

typedef struct ActionInfo {
    u8 type;
    u8 group;
    u8 index;
} ActionInfo;

typedef struct ActionConfig {
    u8 pad0[0x194];
    ActionInfo action;
} ActionConfig;

typedef struct ActionOwner {
    u8 pad0[0x14];
    ActionConfig *config;
    u8 pad18[0x54];
    int state;
} ActionOwner;

typedef struct ActionRef {
    ActionOwner *owner;
    int kind;
} ActionRef;

typedef struct ActionRequest {
    u8 pad0[8];
    int value;
} ActionRequest;

typedef struct ActionTarget {
    int pad0;
    int busy;
    int pad8;
} ActionTarget;

typedef struct SlotInfo {
    u8 padC[0xbd];
    u8 lowBits : 4;
    u8 level : 4;
} SlotInfo;

extern SlotInfo *func_ov001_0208724c(int group, int index);

BOOL CanStartTargetAction(ActionRef *ref, ActionRequest *request, int arg2, int arg3, int arg4, int arg5, ActionTarget *targets, u8 targetCount)
{
    BOOL result = TRUE;
    ActionInfo *config;
    int i;

    if (ref->kind == 4) {
        config = &ref->owner->config->action;
        if (config->type == 1 && ref->owner->state != 0x1a && ref->owner->state != 0x19) {
            result = FALSE;
        }
        if (config->type == 4 && func_ov001_0208724c(config->group, config->index)->level != 0 && request->value == -0x1000) {
            for (i = 0; i < targetCount; i++) {
                if (targets[i].busy == 1) {
                    result = FALSE;
                    break;
                }
            }
        }
    }
    return result;
}
