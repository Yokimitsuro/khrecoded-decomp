#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct MovieOverlayState {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    u8 pad_08[0x8];
    void *overlayTask;
    void *mainTask;
    s32 currentState;
    VecFx32 upVector;
    s32 position;
    u8 pad_2c[0x4];
    s32 target;
    u8 pad_34[0x8];
    s8 fadeMode;
    u8 pad_3d[0x13];
    void *records;
    u8 pad_54[0x68];
    s32 frameCount;
    u8 pad_c0[0x344];
    void *pendingList;
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

typedef s32 (*StateHandler)(void);

extern MovieOverlayState *data_ov031_020bc820;
extern u8 data_ov021_020b52c0[];

extern MovieOverlayState *NNSi_FndGetCurrentRootHeap(void);
extern void ResetSelectionSlots(void);
extern void CreateSessionNameMenu(void);
extern void InitMovieGraphics(void);
extern void func_ov001_0206c6dc(void);
extern void QueueFieldUpdate(int mode);
extern void *CreateOverlayTask(int areaId);
extern int Heap_GetCurrent(void);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void LoadPzTextureParams(void);
extern void ClearFieldCounters(void);
extern s32 RunStateMachine(void);

StateHandler InitMoviePlayerState(MovieEntryParams *params)
{
    TaskDescriptorArgs argsCopy;
    VecFx32 upVector;
    TaskDescriptorArgs args;
    int heapHandle;

    data_ov031_020bc820 = NNSi_FndGetCurrentRootHeap();
    data_ov031_020bc820->areaId = params->areaId;
    data_ov031_020bc820->posX = params->posX;
    data_ov031_020bc820->posY = params->posY;
    upVector.x = 0;
    upVector.y = 0;
    upVector.z = FX32_ONE;
    data_ov031_020bc820->upVector = upVector;
    data_ov031_020bc820->position = 0x333;
    data_ov031_020bc820->target = data_ov031_020bc820->position;
    data_ov031_020bc820->frameCount = 0;
    data_ov031_020bc820->flags = 0x23;
    ResetSelectionSlots();
    CreateSessionNameMenu();
    InitMovieGraphics();
    data_ov031_020bc820->pendingList = NULL;
    func_ov001_0206c6dc();
    QueueFieldUpdate(1);
    data_ov031_020bc820->overlayTask = CreateOverlayTask(params->areaId);
    data_ov031_020bc820->fadeMode = params->fadeMode;
    heapHandle = Heap_GetCurrent();
    args.unk_00 = 2;
    args.heapHandle = heapHandle;
    args.unk_08 = 0;
    argsCopy = args;
    data_ov031_020bc820->mainTask = func_0202a45c(data_ov021_020b52c0, &argsCopy);
    LoadPzTextureParams();
    ClearFieldCounters();
    data_ov031_020bc820->records = NULL;
    data_ov031_020bc820->currentState = 0;
    return RunStateMachine;
}
