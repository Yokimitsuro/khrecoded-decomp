#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    fx32 m[3][3];
} MtxFx33;

typedef struct JointAnimResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} JointAnimResult;

typedef struct CameraAnim {
    u8 pad_00[8];
    void *anmObj;
    u8 pad_0c[4];
    fx32 sinRoll;
    fx32 cosRoll;
    u8 pad_18[4];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
    VecFx32 offset;
} CameraAnim;

extern u8 *NNS_G3dRS;
extern u32 gJointAnimationNodeDispatch;
extern VecFx32 data_020558a0;
extern s16 data_02053580[];

extern void NNSi_G3dAnmCalcNsBca(JointAnimResult *result, void *anmObj, u32 index);
extern void func_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void AdvanceAnimFrame(CameraAnim *anim);

void CamAnim_ApplyPose(CameraAnim *anim)
{
    VecFx32 up;
    JointAnimResult roll;
    JointAnimResult eye;
    fx32 scaleX, scaleY, scaleZ;
    fx32 targetX, targetY, targetZ;
    fx32 angle;
    int index;

    *(u32 *)(NNS_G3dRS + 0xe8) = gJointAnimationNodeDispatch;
    NNSi_G3dAnmCalcNsBca(&eye, anim->anmObj, 0);
    NNSi_G3dAnmCalcNsBca(&roll, anim->anmObj, 1);
    up = data_020558a0;
    targetX = eye.trans.x;
    targetZ = eye.trans.z;
    targetY = eye.trans.y;
    anim->target.x = targetX;
    anim->target.y = targetY;
    anim->target.z = targetZ;
    scaleX = eye.scale.x;
    if (scaleX == 0x7ffff000) {
        anim->position.x = 0;
        anim->position.y = -0x1000;
        anim->position.z = 0;
        func_01ff9404(&up, &eye.rot, &anim->up);
        func_01ff9404(&anim->position, &eye.rot, &anim->position);
        VEC_Add(&anim->position, &anim->target, &anim->position);
    } else {
        scaleY = eye.scale.y;
        scaleZ = eye.scale.z;
        anim->position.y = scaleY;
        anim->position.z = scaleZ;
        anim->position.x = scaleX;
        func_01ff9404(&up, &eye.rot, &anim->up);
    }
    VEC_Add(&anim->position, &anim->offset, &anim->position);
    VEC_Add(&anim->target, &anim->offset, &anim->target);
    angle = FX_Mul(FX_Div(roll.trans.x, 0x2000), 0xc00);
    index = (u16)((angle * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    anim->nearClip = roll.trans.y;
    anim->farClip = roll.trans.z;
    anim->sinRoll = data_02053580[index];
    anim->cosRoll = data_02053580[(0x400 - index) & 0xfff];
    AdvanceAnimFrame(anim);
}

