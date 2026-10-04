typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef int fx32;

typedef struct NNSG2dAnimFrame {
    void *pContent;
    u16 frames;
    u16 padding;
} NNSG2dAnimFrame;

typedef struct NNSG2dAnimSequence {
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    int playMode;
    NNSG2dAnimFrame *pAnmFrameArray;
} NNSG2dAnimSequence;

typedef struct NNSG2dAnimController {
    const NNSG2dAnimFrame *pCurrent;
    const NNSG2dAnimFrame *pActiveCurrent;
    BOOL bReverse;
    BOOL bActive;
    fx32 currentTime;
    fx32 speed;
    int overriddenPlayMode;
    const NNSG2dAnimSequence *pAnimSequence;
    u32 callbackFunctor[4];
} NNSG2dAnimController;

typedef struct NNSG2dCellDataBank NNSG2dCellDataBank;

typedef struct NNSG2dSRTControl {
    u32 words[9];
} NNSG2dSRTControl;

typedef struct NNSG2dCellAnimation {
    NNSG2dAnimController animCtrl;
    const void *pCurrentCell;
    const NNSG2dCellDataBank *pCellDataBank;
    u32 cellTransferStateHandle;
    NNSG2dSRTControl srtCtrl;
} NNSG2dCellAnimation;

extern void NNSi_G2dSrtcInitControl(NNSG2dSRTControl *control, int type);
extern void NNS_G2dInitAnimCtrl(NNSG2dAnimController *control);
extern void NNS_G2dSetCellAnimationSequence(NNSG2dCellAnimation *animation,
                                            const NNSG2dAnimSequence *sequence);

void NNS_G2dInitCellAnimation(NNSG2dCellAnimation *animation,
                              const NNSG2dAnimSequence *sequence,
                              const NNSG2dCellDataBank *cellBank)
{
    animation->pCellDataBank = cellBank;
    animation->cellTransferStateHandle = 0xffffffff;
    NNSi_G2dSrtcInitControl(&animation->srtCtrl, 1);
    NNS_G2dInitAnimCtrl(&animation->animCtrl);
    NNS_G2dSetCellAnimationSequence(animation, sequence);
}
