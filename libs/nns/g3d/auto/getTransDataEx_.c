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

void getTransDataEx_(fx32 *translationComponent, fx32 animationFrame, const u32 *trackDescriptor,
                   const NNSG3dResJntAnm *jointAnimation)
{
    const void *keyframeData = (const void *)((const u8 *)jointAnimation + *(trackDescriptor + 1));
    u32 trackFlags = *trackDescriptor;
    u32 lastInterpolatedFrame;
    u32 keyframeIndex;
    fx32 frameFraction;
    int keyframeSpacing;
    u32 keyframeSpacingShift;
    u32 wholeFrame;

    wholeFrame = (u32)(animationFrame >> 12);

    if (wholeFrame == jointAnimation->frameCount - 1) {
        if (!(trackFlags & 0xc0000000)) {
            keyframeIndex = wholeFrame;
        } else if (trackFlags & 0x40000000) {
            keyframeIndex = (wholeFrame >> 1) + (wholeFrame & 1);
        } else {
            keyframeIndex = (wholeFrame >> 2) + (wholeFrame & 3);
        }

        if (jointAnimation->flags & 2) {
            fx32 currentTranslation, nextTranslation;
            frameFraction = animationFrame & (0x1000 - 1);

            if (trackFlags & 0x20000000) {
                const fx16 *compactKeyframes = (const fx16 *)keyframeData;
                currentTranslation = *(compactKeyframes + keyframeIndex);
                nextTranslation = *compactKeyframes;
            } else {
                const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
                currentTranslation = *(fullSizeKeyframes + keyframeIndex);
                nextTranslation = *fullSizeKeyframes;
            }

            *translationComponent = currentTranslation + (((nextTranslation - currentTranslation) * frameFraction) >> 12);
            return;
        } else {
            if (trackFlags & 0x20000000) {
                *translationComponent = *((const fx16 *)keyframeData + keyframeIndex);
            } else {
                *translationComponent = *((const fx32 *)keyframeData + keyframeIndex);
            }
            return;
        }
    }

    if (!(trackFlags & 0xc0000000)) {
        goto TRANS_EX_0;
    }

    lastInterpolatedFrame = (trackFlags & 0x1fff0000) >> 16;

    if (trackFlags & 0x40000000) {
        if (wholeFrame >= lastInterpolatedFrame) {
            keyframeIndex = lastInterpolatedFrame >> 1;
            goto TRANS_EX_0_1;
        } else {
            keyframeIndex = wholeFrame >> 1;
            frameFraction = animationFrame & (0x1000 * 2 - 1);
            keyframeSpacing = 2;
            keyframeSpacingShift = 1;
            goto TRANS_EX;
        }
    } else {
        if (wholeFrame >= lastInterpolatedFrame) {
            keyframeIndex = (wholeFrame >> 2) + (wholeFrame & 3);
            goto TRANS_EX_0_1;
        } else {
            keyframeIndex = wholeFrame >> 2;
            frameFraction = animationFrame & (0x1000 * 4 - 1);
            keyframeSpacing = 4;
            keyframeSpacingShift = 2;
            goto TRANS_EX;
        }
    }

TRANS_EX_0:
    keyframeIndex = (u32)wholeFrame;
TRANS_EX_0_1:
    frameFraction = animationFrame & (0x1000 - 1);
    keyframeSpacing = 1;
    keyframeSpacingShift = 0;
TRANS_EX:
    {
        fx32 currentTranslation, nextTranslation;
        if (trackFlags & 0x20000000) {
            const fx16 *compactKeyframes = (const fx16 *)keyframeData;
            currentTranslation = *(compactKeyframes + keyframeIndex);
            nextTranslation = *(compactKeyframes + keyframeIndex + 1);
        } else {
            const fx32 *fullSizeKeyframes = (const fx32 *)keyframeData;
            currentTranslation = *(fullSizeKeyframes + keyframeIndex);
            nextTranslation = *(fullSizeKeyframes + keyframeIndex + 1);
        }

        *translationComponent = ((currentTranslation * keyframeSpacing) + (((nextTranslation - currentTranslation) * frameFraction) >> 12)) >> keyframeSpacingShift;
    }
}
