#include "nitro/types.h"

typedef int (*SceneStepFn)(void);

extern void InitFileLoader(void);
extern void SoundMgr_Init(int a, int b);
extern void LoadSeqArcIfChanged(int a);
extern void ResetSceneCtl(void);
extern void CreateManagerObjects(void);
extern void SetPendingScene(s32 pendId, s32 pendArg);
extern int UpdateSceneCallback(void);
extern u32 gEngineState;

SceneStepFn InitSceneSystem(void)
{
    InitFileLoader();
    SoundMgr_Init(0, 0);
    LoadSeqArcIfChanged(0);
    ResetSceneCtl();
    CreateManagerObjects();
    SetPendingScene(1, gEngineState);
    return UpdateSceneCallback;
}
