#include "nitro/types.h"

#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG2CNT (*(vu16 *)0x0400000c)

typedef struct BgRequest {
    u8 pad_00[6];
    u16 plane;
    u16 value;
} BgRequest;

BOOL MovieScene_SetBgPriority(void *scene, void *unused, BgRequest *request)
{
    int priority = request->value & 3;

    switch (request->plane) {
    case 1:
        REG_BG0CNT = (REG_BG0CNT & ~3) | priority;
        break;
    case 2:
        REG_BG1CNT = (REG_BG1CNT & ~3) | priority;
        break;
    case 4:
        REG_BG2CNT = (REG_BG2CNT & ~3) | priority;
        break;
    }
    return TRUE;
}
