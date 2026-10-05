#include "nitro/types.h"

typedef struct {
    u8 pad0[4];
    int target;
    u8 pad8[0xbc];
    int lockMode;
} LockOnInfo;

extern u32 Obj_SetHalfwordFC(u32 anim, u32 speed);
extern BOOL IsBit0Set(u32 *flags);

void SyncLockOnAnimSpeed(int entity)
{
    LockOnInfo *lock = (LockOnInfo *)(entity + 0x274);
    u16 speed;
    int i;
    if (lock->lockMode == 2 && lock->target != 0) {
        speed = *(u16 *)(lock->target + 0x84);
        if (speed == 0) {
            if (*(u16 *)(*(int *)(entity + 0x230) + 0x100) != 0) {
                return;
            }
            speed = 0x7fff;
        }
        Obj_SetHalfwordFC(*(int *)(entity + 0x230) + 4, speed);
        for (i = 0; i < 2; i++) {
            if (IsBit0Set((u32 *)(entity + 0xb68 + i * 0x230))) {
                Obj_SetHalfwordFC(entity + 0xb70 + i * 0x230, speed);
            }
        }
    }
}
