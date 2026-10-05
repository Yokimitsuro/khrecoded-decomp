#include "nitro/types.h"

typedef struct {
    u8 pad_000[4];
    u32 flags;
    s32 state;
} EnemyWork;

typedef struct {
    u8 pad_0000[0x1258];
    EnemyWork work;
} Enemy;

BOOL IsEnemyStunnedOrDowned(Enemy *enemy)
{
    EnemyWork *work = &enemy->work;
    BOOL result = FALSE;

    if (work->flags & 0x80000) {
        result = TRUE;
    }
    if (work->state == 2) {
        result = TRUE;
    }
    return result;
}
