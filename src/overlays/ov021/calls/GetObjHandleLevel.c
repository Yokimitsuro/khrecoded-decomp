#include "nitro/types.h"

typedef struct HandleInfo {
    u8 pad00[0x18];
    u8 baseLevelA;
    u8 baseLevelB;
} HandleInfo;

typedef struct ObjHandle {
    u32 flags;
    u8 player;
    u8 pad05[3];
    HandleInfo *info;
} ObjHandle;

extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern int GetPlayerEntryCount(int player, u32 id);

int GetObjHandleLevel(ObjHandle *handle, int which)
{
    HandleInfo *info = handle->info;
    int level;
    u32 id;

    if (which != 0) {
        level = info->baseLevelB;
        id = 0x13;
        if (IsPlayerEntryFlagSet(handle->player, id)) {
            level += GetPlayerEntryCount(handle->player, id);
        }
    } else {
        level = info->baseLevelA;
        id = 0x12;
        if (IsPlayerEntryFlagSet(handle->player, id)) {
            level += GetPlayerEntryCount(handle->player, id);
        }
    }
    return level;
}
