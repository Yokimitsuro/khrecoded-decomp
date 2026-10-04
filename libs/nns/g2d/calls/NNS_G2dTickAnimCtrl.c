typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef int fx32;
typedef long long s64;

enum {
    NNS_G2D_ANMCALLBACKTYPE_NONE = 0,
    NNS_G2D_ANMCALLBACKTYPE_LAST_FRM,
    NNS_G2D_ANMCALLBACKTYPE_SPEC_FRM,
    NNS_G2D_ANMCALLBACKTYPE_EVER_FRM
};

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

extern int abs(int value);
extern void SequenceEdgeHandle_(NNSG2dAnimController *animCtrl);

static inline u16 GetCurrentFrameIdx_(const NNSG2dAnimController *animCtrl)
{
    return (u16)(((u32)animCtrl->pCurrent -
                  (u32)animCtrl->pAnimSequence->pAnmFrameArray) /
                 sizeof(NNSG2dAnimFrame));
}

static inline BOOL IsAnimCtrlMovingForward_(const NNSG2dAnimController *animCtrl)
{
    return (animCtrl->speed > 0) ^ animCtrl->bReverse ? 1 : 0;
}

static inline BOOL ShouldAnmCtrlMoveNext_(NNSG2dAnimController *animCtrl)
{
    if (animCtrl->bActive &&
        animCtrl->currentTime >= 4096 * (int)animCtrl->pCurrent->frames) {
        return 1;
    }
    return 0;
}

static inline void CallbackFuncHandling_(const NNSG2dCallBackFunctor *functor,
                                         u16 currentFrameIdx)
{
    switch (functor->type) {
    case NNS_G2D_ANMCALLBACKTYPE_SPEC_FRM:
        if (currentFrameIdx == functor->frameIdx) {
            functor->pFunc(functor->param, currentFrameIdx);
        }
        break;
    case NNS_G2D_ANMCALLBACKTYPE_EVER_FRM:
        functor->pFunc(functor->param, currentFrameIdx);
        break;
    }
}

static inline BOOL IsReachStartEdge_(const NNSG2dAnimController *animCtrl,
                                     const NNSG2dAnimFrame *frame)
{
    const NNSG2dAnimFrame *loopBegin =
        animCtrl->pAnimSequence->pAnmFrameArray + animCtrl->pAnimSequence->loopStartFrameIdx;
    return frame <= loopBegin - 1 ? 1 : 0;
}

static inline BOOL IsReachEdge_(const NNSG2dAnimController *animCtrl,
                                const NNSG2dAnimFrame *frame)
{
    if (IsAnimCtrlMovingForward_(animCtrl)) {
        return frame >= animCtrl->pAnimSequence->pAnmFrameArray +
                            animCtrl->pAnimSequence->numFrames ? 1 : 0;
    }
    return IsReachStartEdge_(animCtrl, frame);
}

static inline void MoveNext_(NNSG2dAnimController *animCtrl)
{
    if (IsAnimCtrlMovingForward_(animCtrl)) {
        animCtrl->pCurrent++;
    } else {
        animCtrl->pCurrent--;
    }
}

BOOL NNS_G2dTickAnimCtrl(NNSG2dAnimController *animCtrl, fx32 frames)
{
    BOOL changeFrame = 0;

    if (animCtrl->bActive != 1) {
        return 0;
    }

    animCtrl->currentTime +=
        abs((fx32)(((s64)animCtrl->speed * frames + 0x800) >> 12));

    while (ShouldAnmCtrlMoveNext_(animCtrl)) {
        changeFrame = 1;
        animCtrl->currentTime -= 4096 * (int)animCtrl->pCurrent->frames;
        MoveNext_(animCtrl);

        if (IsReachEdge_(animCtrl, animCtrl->pCurrent)) {
            SequenceEdgeHandle_(animCtrl);
        }

        if (animCtrl->pCurrent->frames != 0) {
            animCtrl->pActiveCurrent = animCtrl->pCurrent;
        }

        if (animCtrl->callbackFunctor.type != NNS_G2D_ANMCALLBACKTYPE_NONE) {
            CallbackFuncHandling_(&animCtrl->callbackFunctor,
                                  GetCurrentFrameIdx_(animCtrl));
        }
    }

    return changeFrame;
}
