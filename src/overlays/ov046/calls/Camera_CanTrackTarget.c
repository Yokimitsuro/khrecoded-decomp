#include "nitro/types.h"

typedef struct TargetInfo {
    u8 pad_00[0x6c];
    s32 type;
} TargetInfo;

typedef struct CameraTarget {
    TargetInfo *info;
    s32 kind;
} CameraTarget;

typedef struct CameraWork {
    u8 pad_00[0xf4];
    s32 locked;
} CameraWork;

extern s32 ContainsMatchingEntry(CameraTarget *target, u32 kind);
extern u32 func_ov046_020c2ad8(CameraWork *work);

BOOL Camera_CanTrackTarget(CameraTarget *target, CameraWork *work)
{
    s32 type;
    s32 kind;

    if (target->kind == 4 && target->info->type == 0x1e) {
        return TRUE;
    }
    if (ContainsMatchingEntry(target, 4)) {
        return FALSE;
    }
    kind = target->kind;
    if (kind == 4) {
        type = target->info->type;
        if ((type == 1 && work->locked == 0) || type == 0x17) {
            return FALSE;
        }
    }
    if (kind != 3 && func_ov046_020c2ad8(work)) {
        return FALSE;
    }
    return TRUE;
}

