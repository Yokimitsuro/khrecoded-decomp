#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u8 group;
} HandleTarget;

typedef struct {
    HandleTarget *target;
} HandleConfig;

typedef struct {
    u8 pad_00[0x10];
    HandleConfig **lists[2];
    int counts[2];
} HandleModeSet;

typedef struct {
    u32 flags;
    u8 pad_04[8];
    HandleModeSet modes[2];
    u8 pad_4c[0x14];
    HandleConfig *config;
} ObjHandle;

extern BOOL IsObjHandleRequirementMet(ObjHandle *handle, int mode);
extern void BeginObjHandleCheck(ObjHandle *handle, HandleConfig *config, int mode);

void AdvanceObjHandleConfig(ObjHandle *handle, int mode)
{
    int next;
    int count;
    int i;
    HandleModeSet *set = &handle->modes[mode];
    int variant = 0;

    if (IsObjHandleRequirementMet(handle, mode)) {
        variant = 1;
    }
    if (handle->config != NULL) {
        count = set->counts[variant];
        for (i = 0; i < set->counts[variant]; i++) {
            if (handle->config == set->lists[variant][i]) {
                next = 0;
                if (i + 1 < count) {
                    next = i + 1;
                }
                BeginObjHandleCheck(handle, set->lists[variant][next], mode);
                return;
            }
        }
    } else {
        BeginObjHandleCheck(handle, set->lists[variant][0], mode);
        return;
    }
    for (i = 0; i < set->counts[variant]; i++) {
        if (handle->config->target->group != set->lists[variant][i]->target->group || set->counts[variant] <= 1) {
            BeginObjHandleCheck(handle, set->lists[variant][i], mode);
            return;
        }
    }
}
