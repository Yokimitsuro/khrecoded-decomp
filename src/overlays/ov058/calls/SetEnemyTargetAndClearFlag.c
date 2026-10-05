#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x1048];
    u8 targetReached;
    u8 pad_1049[0x1264 - 0x1049];
    s32 target;
} EnemyTargetState;

void SetEnemyTargetAndClearFlag(EnemyTargetState *enemy, s32 target)
{
    enemy->target = target;
    enemy->targetReached = 0;
}
