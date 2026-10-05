#include "nitro/types.h"

typedef struct MotionActor {
    u8 pad_000[4];
    u16 isMoving : 1;
    u16 flags4 : 15;
    u16 lowFlags6 : 7;
    u16 isTurning : 1;
    u16 highFlags6 : 8;
    u8 pad_008[0x68];
    int speed;
    int baseSpeed;
    u8 pad_078[0x148];
    int velocityX;
    int velocityZ;
} MotionActor;

extern void func_ov001_020931b0(MotionActor *actor);

void ResetActorMotion(MotionActor *actor, BOOL keepSpeed)
{
    if (!keepSpeed) {
        actor->speed = actor->baseSpeed;
        actor->isMoving = FALSE;
        actor->isTurning = FALSE;
        actor->velocityX = 0;
        actor->velocityZ = 0;
    }
    func_ov001_020931b0(actor);
}
