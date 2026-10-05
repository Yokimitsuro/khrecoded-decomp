#include "nitro/types.h"

typedef struct SceneParams {
    s8 mode;
    s8 sceneId;
    s16 argA;
    s16 argB;
} SceneParams;

typedef struct SceneWork {
    s16 sceneId;
    s16 argA;
    s16 argB;
    s16 state;
    u8 unknown_08[8];
    void *task;
    int handle;
    int counter;
    s8 mode;
    u8 unknown_1d[5];
    s16 colorA;
    s16 colorB;
    u8 unknown_26[0x0a];
    s16 selection;
    u8 unknown_32[0x0a];
    int cursor;
} SceneWork;

extern SceneWork *data_ov035_020bc500;
extern SceneWork *NNSi_FndGetCurrentRootHeap(void);
extern void LoadSlotEntriesFromBits(void);
extern void CreateSessionNameMenu(void);
extern void SetupMovieDisplay(void);
extern void LoadPzTextureParams(void);
extern void func_ov001_0206c6dc(void);
extern void *CreateOverlayTask(int id);
extern void RunMovieSceneFrame(void);

void *InitMovieSceneWork(SceneParams *params) {
    data_ov035_020bc500 = NNSi_FndGetCurrentRootHeap();
    data_ov035_020bc500->sceneId = params->sceneId;
    data_ov035_020bc500->argA = params->argA;
    data_ov035_020bc500->argB = params->argB;
    data_ov035_020bc500->selection = -1;
    data_ov035_020bc500->cursor = -1;
    data_ov035_020bc500->handle = -1;
    data_ov035_020bc500->colorB = 0xff;
    data_ov035_020bc500->colorA = 0xff;
    data_ov035_020bc500->state = 0x23;
    LoadSlotEntriesFromBits();
    CreateSessionNameMenu();
    SetupMovieDisplay();
    LoadPzTextureParams();
    func_ov001_0206c6dc();
    data_ov035_020bc500->task = CreateOverlayTask(data_ov035_020bc500->sceneId);
    data_ov035_020bc500->mode = params->mode;
    data_ov035_020bc500->counter = 0;
    return RunMovieSceneFrame;
}
