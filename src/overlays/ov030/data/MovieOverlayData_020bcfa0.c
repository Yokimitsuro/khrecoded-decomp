#include "nitro/types.h"

typedef int (*SceneStateFunc)(void);

typedef struct {
    u32 id;
    void (*init)(void);
    void (*close)(void);
    u32 workSize;
    u32 flags;
} OverlayDesc;

extern void InitMovieOverlayState_020ba400(void);
extern void MoviePlayer_Close(void);
extern int func_ov030_020ba588(void);
extern int FinishSceneSetup(void);
extern int func_ov030_020ba5e8(void);
extern int func_ov030_020ba614(void);
extern int func_ov030_020ba62c(void);
extern int func_ov030_020ba698(void);
extern int func_ov030_020ba774(void);
extern int func_ov030_020ba7a8(void);
extern int func_ov030_020ba844(void);
extern int func_ov030_020ba874(void);
extern int func_ov030_020ba894(void);
extern int EnterState12WithHalfRate_020ba8f0(void);
extern int func_ov030_020ba90c(void);
extern int func_ov030_020ba930(void);
extern int func_ov030_020ba964(void);
extern int func_ov030_020ba98c(void);
extern int func_ov030_020ba9c8(void);
extern int MoviePlayer_Stop(void);
extern int func_ov030_020baa9c(void);

s32 gMobiClipSourceHandle = -1;

OverlayDesc gMovieOverlayDescriptor = {
    0x2000e, InitMovieOverlayState_020ba400, MoviePlayer_Close, 0x68, 0,
};

SceneStateFunc gMovieSceneStateHandlers[] = {
    func_ov030_020ba588,
    FinishSceneSetup,
    func_ov030_020ba5e8,
    func_ov030_020ba614,
    func_ov030_020ba62c,
    func_ov030_020ba698,
    func_ov030_020ba774,
    func_ov030_020ba7a8,
    func_ov030_020ba844,
    func_ov030_020ba874,
    func_ov030_020ba894,
    EnterState12WithHalfRate_020ba8f0,
    func_ov030_020ba90c,
    func_ov030_020ba930,
    func_ov030_020ba964,
    func_ov030_020ba98c,
    func_ov030_020ba9c8,
    MoviePlayer_Stop,
    func_ov030_020baa9c,
};
