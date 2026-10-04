typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef s32 fx32;

enum {
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP
};

enum {
    NNS_G2D_ANMCALLBACKTYPE_NONE = 0,
    NNS_G2D_ANMCALLBACKTYPE_LAST_FRM,
    NNS_G2D_ANMCALLBACKTYPE_SPEC_FRM,
    NNS_G2D_ANMCALLBACKTYPE_EVER_FRM
};

typedef struct NNSG2dAnimFrameData {
    void *pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrame;

typedef struct NNSG2dAnimSequenceData {
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    s32 playMode;
    NNSG2dAnimFrame *pAnmFrameArray;
} NNSG2dAnimSequence;

typedef void (*NNSG2dAnmCallBackPtr)(u32 data, fx32 currentFrame);

typedef struct NNSG2dCallBackFunctor {
    s32 type;
    u32 param;
    NNSG2dAnmCallBackPtr pFunc;
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
    s32 overriddenPlayMode;
    const NNSG2dAnimSequence *pAnimSequence;
    NNSG2dCallBackFunctor callbackFunctor;
} NNSG2dAnimController;

extern void NNS_G2dResetAnimCtrlState(NNSG2dAnimController *animCtrl);

static inline const NNSG2dAnimFrame *GetFrameBegin_(const NNSG2dAnimSequence *sequence)
{
    return sequence->pAnmFrameArray;
}

static inline const NNSG2dAnimFrame *GetFrameEnd_(const NNSG2dAnimSequence *sequence)
{
    return sequence->pAnmFrameArray + sequence->numFrames;
}

static inline const NNSG2dAnimFrame *GetFrameLoopBegin_(const NNSG2dAnimSequence *sequence)
{
    return sequence->pAnmFrameArray + sequence->loopStartFrameIdx;
}

static inline s32 GetAnimationPlayMode_(const NNSG2dAnimController *animCtrl)
{
    if (animCtrl->overriddenPlayMode != NNS_G2D_ANIMATIONPLAYMODE_INVALID) {
        return animCtrl->overriddenPlayMode;
    }
    return animCtrl->pAnimSequence->playMode;
}

static inline BOOL IsLoopAnimSequence_(const NNSG2dAnimController *animCtrl)
{
    s32 playMode = GetAnimationPlayMode_(animCtrl);
    return (playMode == NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP ||
            playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP) ? 1 : 0;
}

static inline BOOL IsReversePlayAnim_(const NNSG2dAnimController *animCtrl)
{
    s32 playMode = GetAnimationPlayMode_(animCtrl);
    return (playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE ||
            playMode == NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP) ? 1 : 0;
}

static inline BOOL IsReachStartEdge_(const NNSG2dAnimController *animCtrl,
                                     const NNSG2dAnimFrame *frame)
{
    return frame <= GetFrameLoopBegin_(animCtrl->pAnimSequence) - 1 ? 1 : 0;
}

static inline void SequenceEdgeHandleCommon_(NNSG2dAnimController *animCtrl)
{
    if (animCtrl->callbackFunctor.type == NNS_G2D_ANMCALLBACKTYPE_LAST_FRM) {
        animCtrl->callbackFunctor.pFunc(animCtrl->callbackFunctor.param,
                                        animCtrl->currentTime);
    }

    if (!IsLoopAnimSequence_(animCtrl)) {
        animCtrl->bActive = 0;
    } else {
        NNS_G2dResetAnimCtrlState(animCtrl);
    }
}

static inline void SequenceEdgeHandleReverse_(NNSG2dAnimController *animCtrl)
{
    animCtrl->bReverse ^= 1;
    if (IsReachStartEdge_(animCtrl, animCtrl->pCurrent)) {
        SequenceEdgeHandleCommon_(animCtrl);
    }
}

static inline void SequenceEdgeHandleNormal_(NNSG2dAnimController *animCtrl)
{
    SequenceEdgeHandleCommon_(animCtrl);
}

static inline void ValidateAnimFrame_(NNSG2dAnimController *animCtrl,
                                      const NNSG2dAnimFrame **frame)
{
    if (*frame > GetFrameEnd_(animCtrl->pAnimSequence) - 1) {
        *frame = GetFrameEnd_(animCtrl->pAnimSequence) - 1;
    } else if (*frame < GetFrameBegin_(animCtrl->pAnimSequence)) {
        *frame = GetFrameBegin_(animCtrl->pAnimSequence);
    }
}

void SequenceEdgeHandle_(NNSG2dAnimController *animCtrl)
{
    if (IsReversePlayAnim_(animCtrl)) {
        SequenceEdgeHandleReverse_(animCtrl);
    } else {
        SequenceEdgeHandleNormal_(animCtrl);
    }

    ValidateAnimFrame_(animCtrl, &animCtrl->pCurrent);
}
