#include "nitro/types.h"

typedef struct FieldOverlayState {
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
} FieldOverlayState;

typedef struct FieldEntryParams {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
} FieldEntryParams;

typedef struct TaskDescriptorArgs {
    int unk_00;
    int heapHandle;
    int unk_08;
} TaskDescriptorArgs;

typedef int (*StateHandler)(void);

extern FieldOverlayState *data_ov028_020bb3a0;
extern u8 data_020608c8;
extern u8 data_ov021_020b52c0[];
extern u8 data_ov001_0209eb38[];

extern FieldOverlayState *NNSi_FndGetCurrentRootHeap(void);
extern BOOL func_ov001_020645c8(u32 eventId);
extern void func_ov001_020645e8(u32 eventId);
extern void SetupAllSelectionRecords(void);
extern void FillSelectionRecordFromGroup(void);
extern void BuildSelectionEntryList(void);
extern void SyncSelectionRecordFromSlotEntry(void);
extern void func_0204fbb4(void);
extern void RebuildRecordCounters(void);
extern void SetupFlaggedSelectionRecords(void);
extern void FlushPendingFieldUpdate(void);
extern void CreateSessionNameMenu(void);
extern void func_ov028_020baef0(void);
extern void func_ov001_0206c6dc(void);
extern int Heap_GetCurrent(void);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void QueueFieldUpdate(int mode);
extern void *CreateOverlayTask(int areaId);
extern void LoadPzTextureParams(void);
extern int RunSceneStateMachine(void);

StateHandler InitFieldOverlayState(FieldEntryParams *params)
{
    BOOL flagged;
    TaskDescriptorArgs argsCopy;
    TaskDescriptorArgs args;

    data_ov028_020bb3a0 = NNSi_FndGetCurrentRootHeap();
    data_ov028_020bb3a0->areaId = params->areaId;
    data_ov028_020bb3a0->posX = params->posX;
    data_ov028_020bb3a0->posY = params->posY;
    if (func_ov001_020645c8(0x35e3)) {
        SetupAllSelectionRecords();
        FillSelectionRecordFromGroup();
        BuildSelectionEntryList();
        SyncSelectionRecordFromSlotEntry();
        func_0204fbb4();
        RebuildRecordCounters();
        func_ov001_020645e8(0x35e3);
    }
    data_ov028_020bb3a0->flags = 0x23;
    flagged = FALSE;
    if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
        flagged = TRUE;
    }
    if (flagged) {
        u8 previousCount = data_020608c8;
        SetupFlaggedSelectionRecords();
        if (previousCount != data_020608c8) {
            FlushPendingFieldUpdate();
        }
    } else {
        if (data_020608c8 != 1) {
            SyncSelectionRecordFromSlotEntry();
        }
        data_020608c8 = 1;
    }
    CreateSessionNameMenu();
    func_ov028_020baef0();
    func_ov001_0206c6dc();
    args.heapHandle = Heap_GetCurrent();
    args.unk_00 = 0;
    args.unk_08 = 0;
    argsCopy = args;
    data_ov028_020bb3a0->mainTask = func_0202a45c(data_ov021_020b52c0, &argsCopy);
    QueueFieldUpdate(0);
    data_ov028_020bb3a0->overlayTask = CreateOverlayTask(params->areaId);
    data_ov028_020bb3a0->fadeMode = params->fadeMode;
    data_ov028_020bb3a0->subTask = func_0202a45c(data_ov001_0209eb38, NULL);
    LoadPzTextureParams();
    data_ov028_020bb3a0->counter = 0;
    return RunSceneStateMachine;
}
