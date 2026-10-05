typedef unsigned char u8;
typedef unsigned long u32;
typedef signed short fx16;
typedef signed long fx32;
typedef signed long long fx64;

typedef struct NNSG3dResJntAnm NNSG3dResJntAnm;

void ModelAnimation_SampleJointTranslation(fx32 *translationComponent, fx32 animationFrame, const u32 *trackDescriptor,
                   const NNSG3dResJntAnm *jointAnimation)
{
    u32 wholeFrame = (u32)(animationFrame >> 12);
    const void *keyframeData = (const void *)((const u8 *)jointAnimation + *(trackDescriptor + 1));
    u32 trackFlags = *trackDescriptor;
    u32 lastInterpolatedFrame;
    u32 keyframeIndex;
    u32 neighborKeyframeIndex;

    if (!(trackFlags & 0xc0000000)) {
        keyframeIndex = wholeFrame;
        goto TRANS_NONINTERP;
    }

    lastInterpolatedFrame = (trackFlags & 0x1fff0000) >> 16;

    if (trackFlags & 0x40000000) {
        if (wholeFrame & 1) {
            if (wholeFrame > lastInterpolatedFrame) {
                keyframeIndex = (lastInterpolatedFrame >> 1) + 1;
                goto TRANS_NONINTERP;
            } else {
                keyframeIndex = wholeFrame >> 1;
                goto TRANS_INTERP_2;
            }
        } else {
            keyframeIndex = wholeFrame >> 1;
            goto TRANS_NONINTERP;
        }
    } else {
        if (wholeFrame & 3) {
            if (wholeFrame > lastInterpolatedFrame) {
                keyframeIndex = (lastInterpolatedFrame >> 2) + (wholeFrame & 3);
                goto TRANS_NONINTERP;
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
                    keyframeValue = *(compactKeyframes + keyframeIndex);
                    neighborValue = *(compactKeyframes + neighborKeyframeIndex);
                    *translationComponent = (keyframeValue + keyframeValue + keyframeValue + neighborValue) >> 2;
                } else {
                    const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
                    keyframeValue = *(fullSizeKeyframes + keyframeIndex);
                    neighborValue = *(fullSizeKeyframes + neighborKeyframeIndex);
                    *translationComponent = (fx32)(((fx64)keyframeValue + keyframeValue + keyframeValue + neighborValue) >> 2);
                }
                return;
            } else {
                keyframeIndex = wholeFrame >> 2;
                goto TRANS_INTERP_2;
            }
        } else {
            keyframeIndex = wholeFrame >> 2;
            goto TRANS_NONINTERP;
        }
    }

TRANS_INTERP_2:
    if (trackFlags & 0x20000000) {
        const fx16 *compactKeyframes = (const fx16 *)keyframeData;
        *translationComponent = (*(compactKeyframes + keyframeIndex) + *(compactKeyframes + keyframeIndex + 1)) >> 1;
    } else {
        const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
        fx32 nextTranslation = *(fullSizeKeyframes + keyframeIndex) >> 1;
        fx32 v2 = *(fullSizeKeyframes + keyframeIndex + 1) >> 1;
        *translationComponent = nextTranslation + v2;
    }
    return;

TRANS_NONINTERP:
    if (trackFlags & 0x20000000) {
        *translationComponent = *((const fx16 *)keyframeData + keyframeIndex);
    } else {
        *translationComponent = *((const fx32 *)keyframeData + keyframeIndex);
    }
}
