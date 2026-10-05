typedef unsigned char u8;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;
typedef signed long long fx64;

typedef struct NNSG3dResJntAnm NNSG3dResJntAnm;

void getScaleData_(fx32 *scaleAndInverse, fx32 animationFrame, const u32 *trackDescriptor,
                   const NNSG3dResJntAnm *jointAnimation)
{
    u32 wholeFrame = (u32)(animationFrame >> 12);
    const void *keyframeData = (const void *)((u8 *)jointAnimation + *(trackDescriptor + 1));
    u32 trackFlags = *trackDescriptor;
    u32 lastInterpolatedFrame;
    u32 keyframeIndex;
    u32 neighborKeyframeIndex;

    if (!(trackFlags & 0xc0000000)) {
        keyframeIndex = wholeFrame;
        goto SCALE_NONINTERP;
    }

    lastInterpolatedFrame = (trackFlags & 0x1fff0000) >> 16;

    if (trackFlags & 0x40000000) {
        if (wholeFrame & 1) {
            if (wholeFrame > lastInterpolatedFrame) {
                keyframeIndex = (lastInterpolatedFrame >> 1) + 1;
                goto SCALE_NONINTERP;
            } else {
                keyframeIndex = wholeFrame >> 1;
                goto SCALE_INTERP_2;
            }
        } else {
            keyframeIndex = wholeFrame >> 1;
            goto SCALE_NONINTERP;
        }
    } else {
        if (wholeFrame & 3) {
            if (wholeFrame > lastInterpolatedFrame) {
                keyframeIndex = (lastInterpolatedFrame >> 2) + (wholeFrame & 3);
                goto SCALE_NONINTERP;
            }

            if (wholeFrame & 1) {
                fx32 keyframeValue, neighborValue;
                if (wholeFrame & 2) {
                    neighborKeyframeIndex = wholeFrame >> 2;
                    keyframeIndex = neighborKeyframeIndex + 1;
                } else {
                    keyframeIndex = wholeFrame >> 2;
                    neighborKeyframeIndex = keyframeIndex + 1;
                }

                if (trackFlags & 0x20000000) {
                    const fx16 *compactKeyframes = (const fx16 *)keyframeData;
                    keyframeValue = *(compactKeyframes + 2 * keyframeIndex);
                    neighborValue = *(compactKeyframes + 2 * neighborKeyframeIndex);
                    scaleAndInverse[0] = (keyframeValue + (keyframeValue << 1) + neighborValue) >> 2;

                    keyframeValue = *(compactKeyframes + 2 * keyframeIndex + 1);
                    neighborValue = *(compactKeyframes + 2 * neighborKeyframeIndex + 1);
                    scaleAndInverse[1] = (keyframeValue + (keyframeValue << 1) + neighborValue) >> 2;
                } else {
                    const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
                    keyframeValue = *(fullSizeKeyframes + 2 * keyframeIndex);
                    neighborValue = *(fullSizeKeyframes + 2 * neighborKeyframeIndex);
                    scaleAndInverse[0] = (fx32)(((fx64)keyframeValue + keyframeValue + keyframeValue + neighborValue) >> 2);

                    keyframeValue = *(fullSizeKeyframes + 2 * keyframeIndex + 1);
                    neighborValue = *(fullSizeKeyframes + 2 * neighborKeyframeIndex + 1);
                    scaleAndInverse[1] = (fx32)(((fx64)keyframeValue + keyframeValue + keyframeValue + neighborValue) >> 2);
                }
                return;
            } else {
                keyframeIndex = wholeFrame >> 2;
                goto SCALE_INTERP_2;
            }
        } else {
            keyframeIndex = wholeFrame >> 2;
            goto SCALE_NONINTERP;
        }
    }

SCALE_NONINTERP:
    if (trackFlags & 0x20000000) {
        const fx16 *compactKeyframes = (const fx16 *)keyframeData;
        scaleAndInverse[0] = *(compactKeyframes + 2 * keyframeIndex);
        scaleAndInverse[1] = *(compactKeyframes + 2 * keyframeIndex + 1);
    } else {
        const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
        scaleAndInverse[0] = *(fullSizeKeyframes + 2 * keyframeIndex);
        scaleAndInverse[1] = *(fullSizeKeyframes + 2 * keyframeIndex + 1);
    }
    return;

SCALE_INTERP_2:
    if (trackFlags & 0x20000000) {
        const fx16 *compactKeyframes = (const fx16 *)keyframeData;
        scaleAndInverse[0] = (*(compactKeyframes + 2 * keyframeIndex) + *(compactKeyframes + 2 * keyframeIndex + 2)) >> 1;
        scaleAndInverse[1] = (*(compactKeyframes + 2 * keyframeIndex + 1) + *(compactKeyframes + 2 * keyframeIndex + 3)) >> 1;
    } else {
        const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
        scaleAndInverse[0] = (*(fullSizeKeyframes + 2 * keyframeIndex) + (*(fullSizeKeyframes + 2 * keyframeIndex + 2))) >> 1;
        scaleAndInverse[1] = (*(fullSizeKeyframes + 2 * keyframeIndex + 1) + (*(fullSizeKeyframes + 2 * keyframeIndex + 3))) >> 1;
    }
}
