#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_0000[0x4e5];
    u8 alwaysAlert;
    u8 pad_04e6[0x9c0 - 0x4e6];
    s32 actionState;
    u8 pad_09c4[0xa0c - 0x9c4];
    fx32 reachBelow;
} Enemy;

extern Enemy *data_ov058_020d8a40;
extern const s16 data_02053580[];
extern VecFx32 *func_ov052_020ceb74(Enemy *enemy);
extern u16 GetLinkedAngleOffset(Enemy *enemy);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

BOOL IsFacedByPlayer(Enemy *enemy, VecFx32 *outDirection)
{
    VecFx32 *enemyPos = func_ov052_020ceb74(enemy);
    VecFx32 *playerPos = func_ov052_020ceb74(data_ov058_020d8a40);
    fx32 height;
    BOOL inRange;
    fx32 length;
    int angleIndex;
    VecFx32 toEnemy;
    VecFx32 facing;

    VEC_Distance(playerPos, enemyPos);
    inRange = FALSE;
    VEC_Subtract(enemyPos, playerPos, &toEnemy);
    height = toEnemy.y;
    toEnemy.y = 0;
    length = func_01ffaff4(&toEnemy, &toEnemy);
    switch (data_ov058_020d8a40->actionState) {
    case 1:
    case 8:
        if (length < 0x1e00) {
            inRange = TRUE;
        }
        break;
    case 3:
    case 0x13:
        if (length < 0x1e00 && height < 0 && enemy->reachBelow >= -height) {
            inRange = TRUE;
        }
        break;
    }
    if (inRange) {
        angleIndex = GetLinkedAngleOffset(data_ov058_020d8a40) >> 4;
        facing.x = -data_02053580[angleIndex];
        facing.y = 0;
        facing.z = -data_02053580[(0x400 - angleIndex) & 0xfff];
        facing.y = 0;
        VEC_Normalize(&facing, &facing);
        if (VEC_DotProduct(&facing, &toEnemy) > 0x800) {
            *outDirection = toEnemy;
            return TRUE;
        }
    }
    return enemy->alwaysAlert != 0;
}
