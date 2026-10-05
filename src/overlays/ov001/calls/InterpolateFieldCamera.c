#pragma thumb on
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldCamera {
    fx32 rollSin;
    fx32 rollCos;
    u8 pad_08[0xc];
    VecFx32 eye;
    VecFx32 target;
    VecFx32 up;
    VecFx32 focus;
    VecFx32 offset;
    VecFx32 curFocus;
    VecFx32 curOffset;
    VecFx32 prevEye;
    VecFx32 prevTarget;
    fx32 speed;
    s32 roll;
    fx32 curSpeed;
    s32 curRoll;
    s32 timer;
    s32 duration;
    s32 state;
    s32 actorId;
    u8 pad_a0[0xb4 - 0xa0];
    VecFx32 ctrlEye;
    u8 pad_c0[0xd8 - 0xc0];
    VecFx32 ctrlFocus;
    VecFx32 ctrlOffset;
    u8 pad_f0[0x120 - 0xf0];
    fx32 ctrlSpeed;
    s32 ctrlRoll;
    u8 pad_128[0x1ec - 0x128];
    s32 eased;
} FieldCamera;

typedef struct CameraMtx {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} CameraMtx;

typedef struct CameraActor {
    u8 pad_00[0xa8];
    VecFx32 position;
} CameraActor;

extern FieldCamera *data_ov001_020a0514;
extern const s16 data_02053580[];

extern fx32 EvaluateInterpolationCurve(int curve, int duration, int timer);
extern fx32 ScaleAroundPivot(fx32 t, fx32 to, fx32 from);
extern fx32 Anim_InterpEased(fx32 t, fx32 p0, fx32 p1, fx32 p2);
extern CameraActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 t, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void func_01ff9b70(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target, CameraMtx *mtx);

void InterpolateFieldCamera(VecFx32 *outFocus, VecFx32 *outOffset, fx32 *outSpeed, s32 *outRoll)
{
    fx32 t;
    FieldCamera *cam = data_ov001_020a0514;
    VecFx32 eye;
    VecFx32 delta;
    VecFx32 offset;
    VecFx32 focus;
    CameraMtx mtx;
    VecFx32 side;
    VecFx32 forward;
    fx32 speed;
    s32 roll;

    t = 0;
    if (outOffset == NULL && cam->timer > 0) {
        cam->timer--;
    }
    if (cam->timer > 0) {
        t = EvaluateInterpolationCurve(cam->state, cam->duration, cam->timer);
    }
    if (cam->timer == 0) {
        focus = cam->focus;
        if (cam->actorId != -1) {
            eye = ActorRegistry_GetEntityByIndex((u16)cam->actorId)->position;
            VEC_Add(&eye, &focus, &eye);
        } else {
            eye = focus;
        }
        offset = cam->offset;
        speed = cam->speed;
        roll = cam->roll;
    } else if (cam->eased != 0) {
        t <<= 1;
        focus.x = Anim_InterpEased(t, cam->curFocus.x, cam->ctrlFocus.x, cam->focus.x);
        focus.y = Anim_InterpEased(t, cam->curFocus.y, cam->ctrlFocus.y, cam->focus.y);
        focus.z = Anim_InterpEased(t, cam->curFocus.z, cam->ctrlFocus.z, cam->focus.z);
        if (cam->actorId != -1) {
            eye = ActorRegistry_GetEntityByIndex((u16)cam->actorId)->position;
            VEC_Add(&eye, &focus, &eye);
        } else {
            eye = focus;
        }
        cam->eye.x = Anim_InterpEased(t, cam->prevEye.x, cam->ctrlEye.x, eye.x);
        cam->eye.y = Anim_InterpEased(t, cam->prevEye.y, cam->ctrlEye.y, eye.y);
        cam->eye.z = Anim_InterpEased(t, cam->prevEye.z, cam->ctrlEye.z, eye.z);
        offset.x = Anim_InterpEased(t, cam->curOffset.x, cam->ctrlOffset.x, cam->offset.x);
        offset.y = Anim_InterpEased(t, cam->curOffset.y, cam->ctrlOffset.y, cam->offset.y);
        offset.z = Anim_InterpEased(t, cam->curOffset.z, cam->ctrlOffset.z, cam->offset.z);
        speed = Anim_InterpEased(t, cam->curSpeed, cam->ctrlSpeed, cam->speed);
        if (speed < 0x19a) {
            speed = 0x19a;
        }
        roll = Anim_InterpEased(t, cam->curRoll, cam->ctrlRoll, cam->roll);
    } else {
        s16 dy;
        s16 dz;
        focus.x = ScaleAroundPivot(t, cam->focus.x, cam->curFocus.x);
        focus.y = ScaleAroundPivot(t, cam->focus.y, cam->curFocus.y);
        focus.z = ScaleAroundPivot(t, cam->focus.z, cam->curFocus.z);
        if (cam->actorId != -1) {
            eye = ActorRegistry_GetEntityByIndex((u16)cam->actorId)->position;
            VEC_Add(&eye, &focus, &eye);
        } else {
            eye = focus;
        }
        VEC_Subtract(&eye, &cam->prevEye, &delta);
        VEC_MultAdd(t, &delta, &cam->prevEye, &cam->eye);
        dy = cam->offset.y - cam->curOffset.y;
        dz = cam->offset.z - cam->curOffset.z;
        offset.x = (u16)(cam->curOffset.x + ScaleAroundPivot(t, (s16)(cam->offset.x - cam->curOffset.x), 0));
        offset.y = (u16)(cam->curOffset.y + ScaleAroundPivot(t, dy, 0));
        offset.z = (u16)(cam->curOffset.z + ScaleAroundPivot(t, dz, 0));
        speed = ScaleAroundPivot(t, cam->speed, cam->curSpeed);
        roll = ScaleAroundPivot(t, cam->roll, cam->curRoll);
    }
    cam->eye = eye;
    if (outOffset == NULL) {
        fx32 cosPitch;
        int yawIdx;
        int pitch;
        fx32 cosYaw;
        fx32 sinYaw;
        fx32 cosAngle;
        fx32 sinAngle;
        int idx;
        int rollIdx;

        offset.x = (u16)(0x3ffc - offset.x);
        offset.y = (u16)(-offset.y);
        offset.z = (u16)(-offset.z);
        rollIdx = (u16)roll >> 4;
        cam->rollSin = data_02053580[rollIdx];
        cam->rollCos = data_02053580[(0x400 - rollIdx) & 0xfff];
        pitch = offset.y;
        idx = pitch >> 4;
        cosPitch = data_02053580[(0x400 - idx) & 0xfff];
        yawIdx = offset.x >> 4;
        cosYaw = data_02053580[(0x400 - yawIdx) & 0xfff];
        cam->target.x = cam->eye.x + FX_Mul(FX_Mul(speed, cosYaw), cosPitch);
        sinYaw = data_02053580[yawIdx];
        cam->target.z = cam->eye.z + FX_Mul(FX_Mul(speed, sinYaw), cosPitch);
        cam->target.y = cam->eye.y + FX_Mul(speed, data_02053580[idx]);
        idx = (u16)(pitch + 0x1922) >> 4;
        cosAngle = data_02053580[(0x400 - idx) & 0xfff];
        cam->up.x = FX_Mul(cosYaw, cosAngle);
        cam->up.z = FX_Mul(sinYaw, cosAngle);
        cam->up.y = data_02053580[idx];
        func_01ff9b70(&cam->target, &cam->up, &cam->eye, &mtx);
        side.x = mtx._00;
        side.y = mtx._10;
        side.z = mtx._20;
        cam->up.x = mtx._01;
        cam->up.y = mtx._11;
        cam->up.z = mtx._21;
        forward.x = mtx._02;
        forward.y = mtx._12;
        forward.z = mtx._22;
        idx = offset.z >> 4;
        cosAngle = data_02053580[(0x400 - idx) & 0xfff];
        side.x = FX_Mul(side.x, cosAngle);
        side.y = FX_Mul(side.y, cosAngle);
        side.z = FX_Mul(side.z, cosAngle);
        sinAngle = data_02053580[idx];
        side.x += FX_Mul(cam->up.x, sinAngle);
        side.y += FX_Mul(cam->up.y, sinAngle);
        side.z += FX_Mul(cam->up.z, sinAngle);
        VEC_CrossProduct(&forward, &side, &cam->up);
        VEC_Normalize(&cam->up, &cam->up);
        return;
    }
    *outOffset = offset;
    if (outFocus != NULL) {
        *outFocus = focus;
    }
    if (outSpeed != NULL) {
        *outSpeed = speed;
    }
    if (outRoll != NULL) {
        *outRoll = roll;
    }
}
