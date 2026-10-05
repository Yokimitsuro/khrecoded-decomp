#include "nitro/types.h"

typedef struct SceneContext {
    u8 pad_00[0x23];
    s8 progress;
    u8 pad_24[2];
    s8 stage;
    u8 pad_27[0x51];
    s32 stageMode;
    u8 pad_7c[4];
    s32 refreshPending;
    s32 refreshTimer;
} SceneContext;

typedef struct PackedFileView {
    u8 data[0xc];
} PackedFileView;

typedef struct SceneState {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    s8 fadeMode;
    u8 pad_09[0x0B];
    void *overlayTask;
    void *mainTask;
    void *subTask;
    void *menuTask;
    PackedFileView fileView;
    s32 unk_30;
    s32 unk_34;
    u8 pad_38[4];
    s32 unk_3c;
    s32 unk_40;
} SceneState;

typedef struct Ov032Globals {
    SceneContext *context;
    SceneState *scene;
} Ov032Globals;

typedef struct SceneEntryParams {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
} SceneEntryParams;

typedef struct TaskDescriptorArgs {
    int unk_00;
    int heapHandle;
    int unk_08;
} TaskDescriptorArgs;

typedef int (*StateHandler)(void);

extern Ov032Globals data_ov032_020c0080;
extern u8 data_020608c8;
extern u8 data_ov021_020b52c0[];
extern u8 data_ov001_0209eb38[];
extern char sOv032_UiBtlStrLanguageP2_020c0040[];
extern u8 data_ov032_020c0050[];

extern SceneState *NNSi_FndGetCurrentRootHeap(void);
extern BOOL func_ov001_020645c8(u32 eventId);
extern void SetupFlaggedSelectionRecords(void);
extern void FlushPendingFieldUpdate(void);
extern void CreateSessionNameMenu(void);
extern void InitMovieGraphics_020bb3c0(void);
extern void func_ov001_0206c6dc(void);
extern int Heap_GetCurrent(void);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void QueueFieldUpdate(int mode);
extern void *CreateOverlayTask(int areaId);
extern SceneContext *func_ov001_0206468c(s32 index);
extern u32 Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void LoadPackedFileView(PackedFileView *view, u32 fileId, BOOL fromTail);
extern int ZeroHalfThenFree(u32 header);
extern void UploadGroupMenuTiles(int alternate);
extern void SetGroupMenuPercent(int percent);
extern void LoadPzTextureParams(void);
extern void ApplySlotStyleToSession(void);
extern int RunSceneStateMachine_020ba7b0(void);

StateHandler InitSceneOverlayState(SceneEntryParams *params)
{
    TaskDescriptorArgs argsCopy;
    TaskDescriptorArgs args;
    u32 header;

    data_ov032_020c0080.scene = NNSi_FndGetCurrentRootHeap();
    data_ov032_020c0080.scene->areaId = params->areaId;
    data_ov032_020c0080.scene->posX = params->posX;
    data_ov032_020c0080.scene->posY = params->posY;
    data_ov032_020c0080.scene->unk_40 = 0;
    data_ov032_020c0080.scene->flags = 0x23;
    if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
        u8 previousCount = data_020608c8;
        SetupFlaggedSelectionRecords();
        if (previousCount != data_020608c8) {
            FlushPendingFieldUpdate();
        }
    }
    CreateSessionNameMenu();
    InitMovieGraphics_020bb3c0();
    func_ov001_0206c6dc();
    args.heapHandle = Heap_GetCurrent();
    args.unk_00 = 0;
    args.unk_08 = 0;
    argsCopy = args;
    data_ov032_020c0080.scene->mainTask = func_0202a45c(data_ov021_020b52c0, &argsCopy);
    QueueFieldUpdate(0);
    data_ov032_020c0080.scene->overlayTask = CreateOverlayTask(params->areaId);
    data_ov032_020c0080.scene->fadeMode = params->fadeMode;
    data_ov032_020c0080.scene->subTask = func_0202a45c(data_ov001_0209eb38, NULL);
    data_ov032_020c0080.context = func_ov001_0206468c(10);
    header = Msg_OpenContainerAndReadHeader(sOv032_UiBtlStrLanguageP2_020c0040, 0xe, FALSE);
    LoadPackedFileView(&data_ov032_020c0080.scene->fileView, ((header + 0x8000) & 0xfffffc) << 7 | 0x80000007, TRUE);
    ZeroHalfThenFree(header);
    if (data_ov032_020c0080.context->stage < 0) {
        data_ov032_020c0080.scene->menuTask = (void *)-1;
    } else {
        data_ov032_020c0080.scene->menuTask = func_0202a45c(data_ov032_020c0050, NULL);
        if (data_ov032_020c0080.context->stage >= 15 ||
            (data_ov032_020c0080.context->stage == 11 && data_ov032_020c0080.context->stageMode == 1 &&
             data_ov032_020c0080.context->progress == -1)) {
            UploadGroupMenuTiles(FALSE);
        } else {
            UploadGroupMenuTiles(TRUE);
        }
        if (data_ov032_020c0080.context->progress == -1) {
            SetGroupMenuPercent(100);
        } else {
            SetGroupMenuPercent(data_ov032_020c0080.context->progress);
        }
    }
    LoadPzTextureParams();
    data_ov032_020c0080.scene->unk_30 = 0;
    data_ov032_020c0080.context->refreshPending = 0;
    data_ov032_020c0080.context->refreshTimer = 0;
    data_ov032_020c0080.scene->unk_34 = 0;
    data_ov032_020c0080.scene->unk_3c = 8;
    ApplySlotStyleToSession();
    return RunSceneStateMachine_020ba7b0;
}
