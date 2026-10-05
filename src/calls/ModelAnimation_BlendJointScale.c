typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;

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
} NNSG3dResJntAnm;

void ModelAnimation_BlendJointScale(fx32 *scaleAndInverse, fx32 animationFrame, const u32 *trackDescriptor,
                   const NNSG3dResJntAnm *jointAnimation)
{
    const void *keyframeData = (const void *)((const u8 *)jointAnimation + *(trackDescriptor + 1));
    u32 trackFlags = *trackDescriptor;
    u32 lastInterpolatedFrame;
    u32 currentKeyframeIndex, nextKeyframeIndex;
    fx32 frameFraction;
    int keyframeSpacing;
    u32 keyframeSpacingShift;
    u32 wholeFrame;

    wholeFrame = (u32)(animationFrame >> 12);

    if (wholeFrame == jointAnimation->frameCount - 1) {
        if (!(trackFlags & 0xc0000000)) {
            currentKeyframeIndex = wholeFrame;
        } else if (trackFlags & 0x40000000) {
            currentKeyframeIndex = (wholeFrame >> 1) + (wholeFrame & 1);
        } else {
            currentKeyframeIndex = (wholeFrame >> 2) + (wholeFrame & 3);
        }

        if (jointAnimation->flags & 2) {
            nextKeyframeIndex = 0;
            goto SCALE_EX_0_1;
        } else {
            if (trackFlags & 0x20000000) {
                const fx16 *compactKeyframes = (const fx16 *)keyframeData;
                scaleAndInverse[0] = *(compactKeyframes + 2 * currentKeyframeIndex);
                scaleAndInverse[1] = *(compactKeyframes + 2 * currentKeyframeIndex + 1);
            } else {
                const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
                scaleAndInverse[0] = *(fullSizeKeyframes + 2 * currentKeyframeIndex);
                scaleAndInverse[1] = *(fullSizeKeyframes + 2 * currentKeyframeIndex + 1);
            }
            return;
        }
    }

    if (!(trackFlags & 0xc0000000)) {
        goto SCALE_EX_0;
    }

    lastInterpolatedFrame = (trackFlags & 0x1fff0000) >> 16;

    if (trackFlags & 0x40000000) {
        if (wholeFrame >= lastInterpolatedFrame) {
            currentKeyframeIndex = lastInterpolatedFrame >> 1;
            nextKeyframeIndex = currentKeyframeIndex + 1;
            goto SCALE_EX_0_1;
        } else {
            currentKeyframeIndex = wholeFrame >> 1;
            nextKeyframeIndex = currentKeyframeIndex + 1;
            frameFraction = animationFrame & (0x1000 * 2 - 1);
            keyframeSpacing = 2;
            keyframeSpacingShift = 1;
            goto SCALE_EX;
        }
    } else {
        if (wholeFrame >= lastInterpolatedFrame) {
            currentKeyframeIndex = (wholeFrame >> 2) + (wholeFrame & 3);
            nextKeyframeIndex = currentKeyframeIndex + 1;
            goto SCALE_EX_0_1;
        } else {
            currentKeyframeIndex = wholeFrame >> 2;
            nextKeyframeIndex = currentKeyframeIndex + 1;
            frameFraction = animationFrame & (0x1000 * 4 - 1);
            keyframeSpacing = 4;
            keyframeSpacingShift = 2;
            goto SCALE_EX;
        }
    }

SCALE_EX_0:
    currentKeyframeIndex = (u32)wholeFrame;
    nextKeyframeIndex = currentKeyframeIndex + 1;
SCALE_EX_0_1:
    frameFraction = animationFrame & (0x1000 - 1);
    keyframeSpacing = 1;
    keyframeSpacingShift = 0;
SCALE_EX:
    {
        fx32 currentScale, nextScale;
        fx32 currentInverseScale, nextInverseScale;

        if (trackFlags & 0x20000000) {
            const fx16 *compactKeyframes = (const fx16 *)keyframeData;
            currentScale = *(compactKeyframes + 2 * currentKeyframeIndex);
            currentInverseScale = *(compactKeyframes + 2 * currentKeyframeIndex + 1);
            nextScale = *(compactKeyframes + 2 * nextKeyframeIndex);
            nextInverseScale = *(compactKeyframes + 2 * nextKeyframeIndex + 1);
        } else {
            const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
            currentScale = *(fullSizeKeyframes + 2 * currentKeyframeIndex);
            currentInverseScale = *(fullSizeKeyframes + 2 * currentKeyframeIndex + 1);
            nextScale = *(fullSizeKeyframes + 2 * nextKeyframeIndex);
            nextInverseScale = *(fullSizeKeyframes + 2 * nextKeyframeIndex + 1);
        }

        scaleAndInverse[0] = ((currentScale * keyframeSpacing) + (((nextScale - currentScale) * frameFraction) >> 12)) >> keyframeSpacingShift;
        scaleAndInverse[1] = ((currentInverseScale * keyframeSpacing) + (((nextInverseScale - currentInverseScale) * frameFraction) >> 12)) >> keyframeSpacingShift;
    }
}
