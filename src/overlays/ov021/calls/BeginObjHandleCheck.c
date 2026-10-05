#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    u16 flags;
} HandleTarget;

typedef struct {
    HandleTarget *target;
    u32 pad_04;
    s32 type;
} HandleConfig;

typedef struct {
    u32 flags;
    u8 pad_04[0x5c];
    HandleConfig *config;
    s32 counter;
} ObjHandle;

extern void ResetModelGroup(HandleTarget *target);
extern BOOL IsObjHandleRequirementMet(ObjHandle *handle, int mode);

void BeginObjHandleCheck(ObjHandle *handle, HandleConfig *config, int mode)
{
    HandleTarget *target;
    s32 counter;

    handle->config = config;
    handle->flags &= ~0xf;
    ResetModelGroup(config->target);
    target = handle->config->target;
    if (mode == 0) {
        if (config->type != 4) {
            handle->flags |= 1;
            target->flags |= 0x40;
        } else {
            handle->flags |= 2;
        }
    } else if (mode == 1) {
        if (config->type != 5) {
            handle->flags |= 2;
        } else {
            handle->flags |= 1;
            target->flags |= 0x40;
        }
    }
    if (handle->counter == 0) {
        handle->flags |= 4;
    }
    if (IsObjHandleRequirementMet(handle, mode)) {
        handle->flags |= 8;
    }
    counter = handle->counter + 1;
    if (counter > 99) {
        counter = 99;
    } else if (counter < 0) {
        counter = 0;
    }
    handle->counter = counter;
}
