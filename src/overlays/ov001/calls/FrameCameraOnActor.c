#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

typedef struct {
    s32 yaw;
    s32 pitch;
    s32 roll;
} CameraAngles;

typedef struct {
    u8 pad_000[0x44];
    s32 yaw;
    u8 pad_048[0x4];
    s32 roll;
    u8 pad_050[0x30];
    fx32 distance;
    s32 fov;
    u8 pad_088[0x10];
    s32 state;
    u8 pad_09C[0x144];
    s32 savedYaw;
} FieldCamera;

extern FieldCamera *data_ov001_020a0514;

extern VecFx32 *func_ov001_0206dc4c(int index);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern s32 SnapAngleTowardQuadrant(s32 yaw, s32 target, int arg);
extern BOOL func_ov001_020645c8(int bitId);
extern void func_ov001_020645e8(int bitId);
extern BOOL ResolveBlockedAngle(fx32 distance, s32 yaw, s32 currentYaw, CameraAngles *angles);
extern int QueryWithTemporaryCamera(CameraAngles *angles, VecFx32 *focus, fx32 distance, int actorId);
extern fx32 GetActorModeThreeTarget(int actorId);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void SetFieldCameraTarget(int mode, int frames, fx32 distance, s32 fov, VecFx32 *focus, CameraAngles *angles);

void FrameCameraOnActor(int actorId) {
    VecFx32 *target;
    FieldCamera *camera;
    s32 heading;
    fx32 deltaX;
    fx32 deltaZ;
    VecFx32 actorPos;
    VecFx32 focus;
    CameraAngles angles;
    fx32 distance;
    fx32 headroom;
    int result;

    camera = data_ov001_020a0514;
    target = func_ov001_0206dc4c(0);
    actorPos = ActorRegistry_GetEntityByIndex(actorId)->position;
    deltaX = target->x - actorPos.x;
    deltaZ = target->z - actorPos.z;
    camera->yaw &= 0xffff;
    heading = 0x13fff - FX_Atan2Idx(deltaZ, deltaX);
    angles.yaw = SnapAngleTowardQuadrant(camera->yaw, heading, 0);
    angles.pitch = -0x7d2;
    angles.roll = camera->roll;
    if (!func_ov001_020645c8(0x363b)) {
        if (!ResolveBlockedAngle(camera->distance, angles.yaw, camera->yaw, &angles)) {
            return;
        }
    } else {
        func_ov001_020645e8(0x363b);
    }
    distance = camera->distance;
    if (distance < 0x1800) {
        distance = 0x1800;
    } else if (distance >= 0x2800) {
        distance = 0x2800;
    }
    focus.x = (target->x + actorPos.x) / 2;
    focus.y = (target->y + actorPos.y) / 2;
    focus.z = (target->z + actorPos.z) / 2;
    result = QueryWithTemporaryCamera(&angles, &focus, distance, actorId);
    headroom = 0x1666 - GetActorModeThreeTarget(actorId);
    if (result == 1) {
        if (distance == 0x1800) {
            focus.y += 0x14cd;
        } else {
            focus.y += 0x1000;
        }
        if (headroom > 0xd9a) {
            headroom = FX_Mul(headroom, 0x666);
        } else if (headroom > 0) {
            headroom = FX_Mul(headroom, 0x333);
        }
        focus.y -= headroom;
    } else {
        focus.y += 0x1800;
        if (headroom > 0xccd) {
            headroom = FX_Mul(headroom, 0xb33);
        } else if (headroom < 0) {
            headroom = FX_Mul(headroom, 0x800);
        }
        focus.y -= headroom;
    }
    camera->savedYaw = camera->yaw;
    camera->state = 5;
    SetFieldCameraTarget(-1, 0xf, distance, camera->fov, &focus, &angles);
}
