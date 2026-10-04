typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef int fx32;

typedef struct NNSG2dAnimFrame {
    void *pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrame;

typedef struct NNSG2dAnimSequence NNSG2dAnimSequence;
typedef void (*NNSG2dAnmCallBackPtr)(u32 data, fx32 currentFrame);

typedef struct NNSG2dCallBackFunctor {
    int type;
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
    int overriddenPlayMode;
    const NNSG2dAnimSequence *pAnimSequence;
    NNSG2dCallBackFunctor callbackFunctor;
} NNSG2dAnimController;

extern void NNS_G2dInitAnimCallBackFunctor(NNSG2dCallBackFunctor *callBack);

void NNS_G2dInitAnimCtrl(NNSG2dAnimController *animCtrl)
{
    NNS_G2dInitAnimCallBackFunctor(&animCtrl->callbackFunctor);
    animCtrl->pCurrent = 0;
    animCtrl->pActiveCurrent = 0;
    animCtrl->bReverse = 0;
    animCtrl->bActive = 1;
    animCtrl->currentTime = 0;
    animCtrl->speed = 4096;
    animCtrl->overriddenPlayMode = 0;
    animCtrl->pAnimSequence = 0;
}
