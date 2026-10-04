typedef void (*NNSG2dAnimCallback)(void *argument);

typedef struct NNSG2dCallBackFunctor {
    int type;
    void *argument;
    NNSG2dAnimCallback callback;
    unsigned short frameIndex;
} NNSG2dCallBackFunctor;

typedef struct NNSG2dAnimController {
    unsigned char padding00[0x20];
    NNSG2dCallBackFunctor callback;
} NNSG2dAnimController;

void NNS_G2dSetAnimCtrlCallBackFunctorAtAnimFrame(
    NNSG2dAnimController *controller,
    void *argument,
    NNSG2dAnimCallback callback,
    unsigned short frameIndex)
{
    controller->callback.type = 2;
    controller->callback.callback = callback;
    controller->callback.argument = argument;
    controller->callback.frameIndex = frameIndex;
}
