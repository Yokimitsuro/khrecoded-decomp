#include "nitro/types.h"

typedef struct TaskManager {
    u8 enabled;
} TaskManager;

extern TaskManager gTaskManager;

u32 TaskManager_SetEnabled(u32 enabled)
{
    gTaskManager.enabled = (u8)enabled;
    return enabled;
}
