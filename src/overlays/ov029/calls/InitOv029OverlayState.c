#include "nitro/types.h"

typedef struct {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    u8 pad_08[4];
    void *mainTask;
    void *subTask;
    int counter;
} Ov029State;

typedef struct {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
} Ov029EntryParams;

typedef struct {
    int unk_00;
    int heapHandle;
    int unk_08;
} TaskDescriptorArgs;

typedef int (*StateHandler)(void);

extern Ov029State *data_ov029_020babc0;
extern u8 data_ov021_020b52c0[];
extern u8 data_ov001_0209eb38[];

extern Ov029State *NNSi_FndGetCurrentRootHeap(void);
extern void CreateSessionNameMenu(void);
extern void func_ov029_020ba8d8(void);
extern void QueueFieldUpdate(int mode);
extern int Heap_GetCurrent(void);
extern void *func_0202a45c(void *descriptor, void *userData);
extern int RunSceneStateMachine_020ba4c4(void);

StateHandler InitOv029OverlayState(Ov029EntryParams *params)
{
    TaskDescriptorArgs argsCopy;
    TaskDescriptorArgs args;

    data_ov029_020babc0 = NNSi_FndGetCurrentRootHeap();
    data_ov029_020babc0->areaId = params->areaId;
    data_ov029_020babc0->posX = params->posX;
    data_ov029_020babc0->posY = params->posY;
    data_ov029_020babc0->flags = 3;
    CreateSessionNameMenu();
    func_ov029_020ba8d8();
    QueueFieldUpdate(0);
    args.heapHandle = Heap_GetCurrent();
    args.unk_00 = 0;
    args.unk_08 = 0;
    argsCopy = args;
    data_ov029_020babc0->mainTask = func_0202a45c(data_ov021_020b52c0, &argsCopy);
    data_ov029_020babc0->subTask = func_0202a45c(data_ov001_0209eb38, NULL);
    data_ov029_020babc0->counter = 0;
    return RunSceneStateMachine_020ba4c4;
}
