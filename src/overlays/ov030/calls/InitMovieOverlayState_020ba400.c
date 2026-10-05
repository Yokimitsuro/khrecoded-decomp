#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct MovieOverlayState {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    s8 fadeMode;
    u8 pad_09[0x0B];
    void *overlayTask;
    void *mainTask;
    void *subTask;
    int counter;
    VecFx32 upVector;
    int frame;
} MovieOverlayState;

typedef struct MovieEntryParams {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
} MovieEntryParams;

typedef struct TaskDescriptorArgs {
    int unk_00;
    int heapHandle;
    int unk_08;
} TaskDescriptorArgs;

typedef struct {
    u8 pad_00[2];
    u16 current;
    u16 initial;
} SelectionRecord;

typedef int (*StateHandler)(void);

extern MovieOverlayState *data_ov030_020bd020;
extern u8 data_ov021_020b52c0[];
extern u8 data_ov001_0209eb38[];

extern MovieOverlayState *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov030_020bc444(void);
extern void CreateSessionNameMenu(void);
extern void func_ov030_020bab20(void);
extern void func_ov001_0206c6dc(void);
extern void QueueFieldUpdate(int mode);
extern void *CreateOverlayTask(int areaId);
extern int Heap_GetCurrent(void);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void LoadPzTextureParams(void);
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern void ClearFieldCounters(void);
extern int RunSceneStateMachine_020ba4e0(void);

StateHandler InitMovieOverlayState_020ba400(MovieEntryParams *params)
{
    TaskDescriptorArgs argsCopy;
    VecFx32 upVector;
    TaskDescriptorArgs args;
    int index;
    int heapHandle;

    data_ov030_020bd020 = NNSi_FndGetCurrentRootHeap();
    data_ov030_020bd020->areaId = params->areaId;
    data_ov030_020bd020->posX = params->posX;
    data_ov030_020bd020->posY = params->posY;
    upVector.x = 0;
    upVector.y = 0;
    upVector.z = FX32_ONE;
    data_ov030_020bd020->upVector = upVector;
    data_ov030_020bd020->flags = 0x23;
    func_ov030_020bc444();
    CreateSessionNameMenu();
    func_ov030_020bab20();
    func_ov001_0206c6dc();
    QueueFieldUpdate(0);
    data_ov030_020bd020->overlayTask = CreateOverlayTask(params->areaId);
    data_ov030_020bd020->fadeMode = params->fadeMode;
    heapHandle = Heap_GetCurrent();
    args.unk_00 = 1;
    args.heapHandle = heapHandle;
    args.unk_08 = 0;
    argsCopy = args;
    data_ov030_020bd020->mainTask = func_0202a45c(data_ov021_020b52c0, &argsCopy);
    data_ov030_020bd020->subTask = func_0202a45c(data_ov001_0209eb38, NULL);
    LoadPzTextureParams();
    data_ov030_020bd020->frame = 0;
    for (index = 0; index < 3; index++) {
        GetOverlaySelectionRecord(index)->current = GetOverlaySelectionRecord(index)->initial;
    }
    ClearFieldCounters();
    data_ov030_020bd020->counter = 0;
    return RunSceneStateMachine_020ba4e0;
}
