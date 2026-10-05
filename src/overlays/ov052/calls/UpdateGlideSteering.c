#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ExitFunc)(Actor *actor, int arg, int value);
typedef void (*FacingFunc)(Actor *actor, u16 angle);
typedef void (*SetModeFunc)(Actor *actor, int mode);

struct Actor {
    u8 pad_0000[0x1f8];
    ExitFunc onModeExit;
    u8 pad_01fc[0x210 - 0x1fc];
    FacingFunc setFacing;
    u8 pad_0214[0x234 - 0x214];
    u32 flags;
    u8 pad_0238[0x75c - 0x238];
    int mode;
    u8 pad_0760[0x9b4 - 0x760];
    u8 player;
    u8 pad_09b5[0x9c4 - 0x9b5];
    int chargeTime;
    VecFx32 velocity;
    u8 pad_09d4[0x9fc - 0x9d4];
    u16 heading;
    u8 pad_09fe[0xa10 - 0x9fe];
    u8 speed[0x10ec - 0xa10];
    SetModeFunc setMode;
};

extern s16 data_02053580[];
extern void *func_ov001_0206db78(int player);
extern BOOL func_ov021_020a7530(void *input);
extern BOOL HasFlagsAt0xe(void *input, u16 mask);
extern int func_ov021_020a7564(void *input);
extern u16 SharedObject_GetField2(void *input);
extern s32 func_ov001_02063a38(void);
extern int StepFacingToward(Actor *actor, u16 heading);
extern int ApproachTargetValue(void *value);
extern int FX_Mul(int left, int right);
extern void UpdateModelTilt(Actor *actor, int heading);

void UpdateGlideSteering(Actor *actor)
{
    void *input = func_ov001_0206db78(actor->player);
    BOOL done = FALSE;
    u32 flagSet = actor->flags & 4;
    int heading = -1;
    fx32 rise = actor->velocity.y;

    if (rise > 0) {
        actor->velocity.y = rise >> 1;
    }
    if (func_ov021_020a7530(input) && !HasFlagsAt0xe(input, 0x100)) {
        if (actor->mode == 0xe) {
            if (actor->onModeExit != NULL) {
                actor->onModeExit(actor, 0xf, -1);
            }
            actor->chargeTime = 0;
        }
        heading = func_ov021_020a7564(input);
    } else if (actor->mode == 0xf) {
        if (func_ov001_02063a38() != 4) {
            heading = actor->heading;
        } else {
            heading = SharedObject_GetField2(input);
        }
    }
    if (heading != -1) {
        int index;
        fx32 speed;
        fx32 dx;
        fx32 dz;
        heading = StepFacingToward(actor, heading);
        index = (u16)heading >> 4;
        speed = ApproachTargetValue(actor->speed);
        dx = FX_Mul(-data_02053580[index], speed);
        dz = FX_Mul(-data_02053580[(0x400 - index) & 0xfff], speed);
        if (actor->setFacing != NULL) {
            actor->setFacing(actor, heading);
        }
        actor->velocity.x += dx;
        actor->velocity.z += dz;
    }
    UpdateModelTilt(actor, heading);
    if (!HasFlagsAt0xe(input, 0x800) && actor->chargeTime >= 0xa000) {
        done = TRUE;
    }
    if (done) {
        if (flagSet) {
            actor->setMode(actor, 5);
            return;
        }
        actor->setMode(actor, 4);
    }
}
