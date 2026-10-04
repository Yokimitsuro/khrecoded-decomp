typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef int fx32;

typedef struct NNSG2dAnimFrame {
    void *pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrame;

typedef struct NNSG2dAnimSequence {
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    int playMode;
    NNSG2dAnimFrame *pAnmFrameArray;
} NNSG2dAnimSequence;

typedef struct NNSG2dCallBackFunctor {
    int type;
    u32 param;
    void (*pFunc)(u32, fx32);
    u16 frameIdx;
    u16 pad16;
} NNSG2dCallBackFunctor;

typedef struct NNSG2dAnimController {
    const NNSG2dAnimFrame *pCurrent;
    const NNSG2dAnimFrame *pActiveCurrent;
    BOOL bReverse;
    BOOL bActive;
    fx32 currentTime;
    fx32 speed;
    int overriddenPlayMode;
    const NNSG2dAnimSequence *pAnimSequence;
    NNSG2dCallBackFunctor callbackFunctor;
} NNSG2dAnimController;

extern BOOL NNS_G2dTickAnimCtrl(NNSG2dAnimController *animCtrl, fx32 frames);

static inline BOOL IsAnimCtrlMovingForward_(const NNSG2dAnimController *animCtrl)
{
    return (animCtrl->speed > 0) ^ animCtrl->bReverse ? 1 : 0;
}

void NNS_G2dResetAnimCtrlState(NNSG2dAnimController *animCtrl)
{
    if (IsAnimCtrlMovingForward_(animCtrl)) {
        animCtrl->pCurrent =
            animCtrl->pAnimSequence->pAnmFrameArray + animCtrl->pAnimSequence->loopStartFrameIdx;
    } else {
        animCtrl->pCurrent =
            animCtrl->pAnimSequence->pAnmFrameArray + animCtrl->pAnimSequence->numFrames - 1;
    }

    animCtrl->pActiveCurrent = animCtrl->pCurrent;
    animCtrl->currentTime = 0;
    (void)NNS_G2dTickAnimCtrl(animCtrl, 0);
}
