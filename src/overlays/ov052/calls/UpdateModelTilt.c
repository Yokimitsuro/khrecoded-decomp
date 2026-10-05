#include "nitro/types.h"

typedef struct {
    u16 flags;
    u8 pad_02[0x7e - 0x02];
    u16 tilt;
} TiltNode;

typedef struct {
    u8 pad_00[4];
    TiltNode node;
} TiltModel;

typedef struct {
    u8 pad_000[0x230];
    TiltModel *model;
    u8 pad_234[0x9b4 - 0x234];
    u8 pool;
    u8 pad_9b5[0x9fc - 0x9b5];
    u16 facing;
} TiltActor;

extern void func_ov001_0206db78(int pool);

void UpdateModelTilt(TiltActor *actor, int targetAngle)
{
    BOOL settle;
    int tilt;
    int diff;
    int step;

    func_ov001_0206db78(actor->pool);
    settle = TRUE;
    tilt = actor->model->node.tilt;
    if (targetAngle != -1) {
        diff = (u16)(targetAngle - actor->facing);
        if ((diff > 100 && diff < 0x8000) || (diff > 0x8000 && diff < 0xff9c)) {
            if (diff > 100 && diff < 0x8000) {
                step = -0x256;
            } else {
                step = 0x256;
            }
            tilt = (u16)(tilt + step);
            if (tilt >= 7000 && tilt <= 0x8000) {
                tilt = 7000;
            } else if (tilt <= 0xe4a8 && tilt > 0x8000) {
                tilt = 0xe4a8;
            }
            settle = FALSE;
        }
    }
    if (settle && tilt != 0) {
        if (tilt > 0x8000) {
            step = 0x256;
        } else {
            step = -0x256;
        }
        tilt = (u16)(tilt + step);
        if (tilt <= 0x256) {
            tilt = 0;
        }
    }
    {
        TiltNode *node = &actor->model->node;
        node->tilt = tilt;
        node->flags |= 0x20;
    }
}
