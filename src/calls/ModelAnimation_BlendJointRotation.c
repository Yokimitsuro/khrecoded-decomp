typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long fx32;
typedef int BOOL;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

typedef struct NNSG3dResAnmHeader {
    u8 category0;
    u8 revision;
    u16 category1;
} NNSG3dResAnmHeader;

typedef struct NNSG3dResJntAnm {
    NNSG3dResAnmHeader anmHeader;
    u16 frameCount;
    u16 jointCount;
    u32 flags;
    u32 compactRotationOffset;
    u32 fullRotationOffset;
} NNSG3dResJntAnm;

extern BOOL func_01ffd56c(MtxFx33 *rotationMatrix, const void *compactRotationData,
                          const void *fullRotationData, u32 trackFlags);
extern void func_01ffcf74(VecFx32 *first, VecFx32 *second);
extern fx32 VEC_Normalize(const VecFx32 *inputVector, VecFx32 *normalizedVector);

static inline void CrossProductFixed(const VecFx32 *firstVector, const VecFx32 *secondVector, VecFx32 *crossProduct)
{
    crossProduct->x = (firstVector->y * secondVector->z - firstVector->z * secondVector->y) >> 12;
    crossProduct->y = (firstVector->z * secondVector->x - firstVector->x * secondVector->z) >> 12;
    crossProduct->z = (firstVector->x * secondVector->y - firstVector->y * secondVector->x) >> 12;
}

void ModelAnimation_BlendJointRotation(MtxFx33 *rotationMatrix, fx32 animationFrame, const u32 *trackDescriptor,
                   const NNSG3dResJntAnm *jointAnimation)
{
    u32 keyframeIndex;
    u32 nextKeyframeIndex;
    fx32 frameFraction;
    u32 keyframeSpacing;
    const void *compactRotationData = (const void *)((const u8 *)jointAnimation + jointAnimation->compactRotationOffset);
    const void *fullRotationData = (const void *)((const u8 *)jointAnimation + jointAnimation->fullRotationOffset);
    u32 trackFlags = trackDescriptor[0];
    const u16 *rotationKeyIndices = (const u16 *)((const u8 *)jointAnimation + trackDescriptor[1]);

    if (jointAnimation->frameCount - 1 == (u32)(animationFrame >> 12)) {
        keyframeIndex = (u32)(animationFrame >> 12);
        if (trackFlags & 0xc0000000) {
            if (trackFlags & 0x40000000) {
                keyframeIndex = (keyframeIndex & 1) + (keyframeIndex >> 1);
            } else {
                keyframeIndex = (keyframeIndex & 3) + (keyframeIndex >> 2);
            }
        }
        if (jointAnimation->flags & 2) {
            nextKeyframeIndex = 0;
            goto DEFAULT_WEIGHT;
        }
        if (func_01ffd56c(rotationMatrix, compactRotationData, fullRotationData, rotationKeyIndices[keyframeIndex])) {
            CrossProductFixed((const VecFx32 *)&rotationMatrix->_00, (const VecFx32 *)&rotationMatrix->_10,
                      (VecFx32 *)&rotationMatrix->_20);
        } else {
            VEC_Normalize((VecFx32 *)&rotationMatrix->_20, (VecFx32 *)&rotationMatrix->_20);
        }
        return;
    }

    keyframeIndex = (u32)(animationFrame >> 12);
    if (trackFlags & 0xc0000000) {
        u32 lastInterpolatedFrame = (trackFlags & 0x1fff0000) >> 16;
        if (trackFlags & 0x40000000) {
            if (keyframeIndex >= lastInterpolatedFrame) {
                keyframeIndex = lastInterpolatedFrame >> 1;
                nextKeyframeIndex = keyframeIndex + 1;
                goto DEFAULT_WEIGHT;
            }
            keyframeIndex = keyframeIndex >> 1;
            nextKeyframeIndex = keyframeIndex + 1;
            keyframeSpacing = 2;
            frameFraction = animationFrame & 0x1fff;
            goto BLEND;
        }
        if (keyframeIndex >= lastInterpolatedFrame) {
            keyframeIndex = (keyframeIndex & 3) + (keyframeIndex >> 2);
            nextKeyframeIndex = keyframeIndex + 1;
            goto DEFAULT_WEIGHT;
        }
        keyframeIndex = keyframeIndex >> 2;
        nextKeyframeIndex = keyframeIndex + 1;
        keyframeSpacing = 4;
        frameFraction = animationFrame & 0x3fff;
        goto BLEND;
    } else {
        nextKeyframeIndex = keyframeIndex + 1;
        goto DEFAULT_WEIGHT;
    }

DEFAULT_WEIGHT:
    frameFraction = animationFrame & 0xfff;
    keyframeSpacing = 1;

BLEND:
    {
        MtxFx33 currentRotation, nextRotation;
        BOOL reconstructThirdAxis = 0;

        reconstructThirdAxis |= func_01ffd56c(&currentRotation, compactRotationData, fullRotationData, rotationKeyIndices[keyframeIndex]);
        reconstructThirdAxis |= func_01ffd56c(&nextRotation, compactRotationData, fullRotationData, rotationKeyIndices[nextKeyframeIndex]);

        rotationMatrix->_00 = currentRotation._00 * keyframeSpacing + ((frameFraction * (nextRotation._00 - currentRotation._00)) >> 12);
        rotationMatrix->_01 = currentRotation._01 * keyframeSpacing + ((frameFraction * (nextRotation._01 - currentRotation._01)) >> 12);
        rotationMatrix->_02 = currentRotation._02 * keyframeSpacing + ((frameFraction * (nextRotation._02 - currentRotation._02)) >> 12);
        rotationMatrix->_10 = currentRotation._10 * keyframeSpacing + ((frameFraction * (nextRotation._10 - currentRotation._10)) >> 12);
        rotationMatrix->_11 = currentRotation._11 * keyframeSpacing + ((frameFraction * (nextRotation._11 - currentRotation._11)) >> 12);
        rotationMatrix->_12 = currentRotation._12 * keyframeSpacing + ((frameFraction * (nextRotation._12 - currentRotation._12)) >> 12);

        func_01ffcf74((VecFx32 *)&rotationMatrix->_00, (VecFx32 *)&rotationMatrix->_10);

        if (!reconstructThirdAxis) {
            rotationMatrix->_20 = currentRotation._20 * keyframeSpacing + ((frameFraction * (nextRotation._20 - currentRotation._20)) >> 12);
            rotationMatrix->_21 = currentRotation._21 * keyframeSpacing + ((frameFraction * (nextRotation._21 - currentRotation._21)) >> 12);
            rotationMatrix->_22 = currentRotation._22 * keyframeSpacing + ((frameFraction * (nextRotation._22 - currentRotation._22)) >> 12);
            VEC_Normalize((VecFx32 *)&rotationMatrix->_20, (VecFx32 *)&rotationMatrix->_20);
        } else {
            CrossProductFixed((const VecFx32 *)&rotationMatrix->_00, (const VecFx32 *)&rotationMatrix->_10,
                      (VecFx32 *)&rotationMatrix->_20);
        }
    }
}
