#include "nitro/types.h"

typedef struct {
    s32 mode;
    u32 flags;
    s32 action;
    u8 pad_0c[4];
    s32 actionArg;
} AiState;

typedef struct {
    u8 pad_000[0x9ac];
    u64 stateFlags;
    u8 pad_9b4[0x9c0 - 0x9b4];
    s32 state;
    u8 pad_9c4[0x1258 - 0x9c4];
    AiState ai;
} Enemy;

extern Enemy *data_ov058_020d8a40;

BOOL TryRequestEnemyAction(Enemy *enemy, int action, int arg)
{
    AiState *ai = &enemy->ai;
    BOOL blocked = FALSE;

    if (ai->action == 3) {
        return FALSE;
    }
    if (ai->action == action) {
        return FALSE;
    }
    if (action != 3) {
        blocked = TRUE;
        if (data_ov058_020d8a40 != NULL) {
            blocked = FALSE;
            if (data_ov058_020d8a40->state == 10 || data_ov058_020d8a40->state == 0x18) {
                blocked = TRUE;
            }
        }
        if (!blocked) {
            switch (enemy->state) {
            case 10:
            case 0x15:
            case 0x16:
            case 0x18:
            case 0x1a:
                blocked = TRUE;
                break;
            }
        }
        if ((enemy->stateFlags & 0x20820) != 0) {
            blocked = TRUE;
        }
    }
    if (blocked) {
        return FALSE;
    }
    ai->action = action;
    ai->actionArg = arg;
    return TRUE;
}
