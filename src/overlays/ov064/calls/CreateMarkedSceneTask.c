#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[2];
    void *arg;
    u32 *resource;
} TaskDesc;

typedef struct {
    u8 pad_00[0x14];
    u32 player;
    u8 pad_18[4];
    u32 resourceBase;
} TaskOwner;

typedef struct {
    int resourceId;
    u32 animationName;
    u32 modelName;
    u32 textureName;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct {
    u32 names[4];
} GroupNameTable;

typedef struct {
    u8 pad_00[0x10];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*draw)();
    void (*cleanup)();
    u8 pad_28[4];
    void (*update)();
    void (*onEvent)();
    u8 pad_34[4];
    void (*onStart)();
    void (*onAction)();
    u32 resourceId;
    u8 pad_44[0x18];
    u16 groups[4];
    u8 pad_64[4];
    void *messages;
    void *cameraPath;
} SceneTask;

extern char sOv064_CmMF_020d8880[];
extern char sOv064_BaEfFnMfP2_020d8888[];
extern const GroupNameTable data_ov064_020d885c;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void CameraPath_Load(void *path, const char *name);
extern void InitScriptTask(SceneTask *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern int func_ov021_020a89c8(EntryGroupDesc *desc);
extern u32 func_ov001_0206dba0(int index);
extern void *AcquireRecordHandle(TaskOwner *owner, void *resDesc, u32 id, u32 key);
extern void LoadResGroupHandles(SceneTask *task, TaskOwner *owner, void *resDesc);
extern void BeginMarkedIntroScene();
extern void func_ov064_020d86d4();
extern void func_ov064_020d86f0();
extern void func_ov064_020d8254();
extern void func_ov064_020d86c4();
extern void UpdateRisingFinisherAction();

SceneTask *CreateMarkedSceneTask(TaskOwner *owner, void *resDesc, TaskDesc *desc)
{
    SceneTask *task = NNSi_FndAllocFromDefaultHeap(sizeof(SceneTask));
    int i;
    EntryGroupDesc group;
    GroupNameTable names;
    void *messages;
    u32 high;
    u32 base;

    task->cameraPath = NNSi_FndAllocFromDefaultHeap(0x60);
    CameraPath_Load(task->cameraPath, sOv064_CmMF_020d8880);
    i = 0;
    InitScriptTask(task, 4, desc->id, desc->arg);
    task->onStart = BeginMarkedIntroScene;
    task->update = func_ov064_020d86d4;
    task->draw = func_ov064_020d86f0;
    task->cleanup = func_ov064_020d8254;
    task->onEvent = func_ov064_020d86c4;
    task->onAction = UpdateRisingFinisherAction;
    names = data_ov064_020d885c;
    messages = Msg_OpenContainerAndReadHeader(sOv064_BaEfFnMfP2_020d8888, owner->player + 8, FALSE);
    ZeroBytes0x14(&group);
    high = ((((u32)messages + 0x8000) & 0xfffffc) << 7) | 0x80000000;
    do {
        group.textureName = ((i * 2) & 0x1ff) | high;
        group.animationName = ((i * 2 + 1) & 0x1ff) | high;
        group.modelName = names.names[i];
        task->groups[i] = func_ov021_020a89c8(&group);
        i++;
    } while (i < 4);
    task->messages = messages;
    task->resourceId = *desc->resource;
    task->handleCount = 1;
    task->handles = NNSi_FndAllocFromDefaultHeap(task->handleCount * 4);
    base = func_ov001_0206dba0(6);
    task->handles[0] = AcquireRecordHandle(owner, resDesc, owner->resourceBase + task->resourceId,
        ((((base + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (task->resourceId & 0x1ff));
    LoadResGroupHandles(task, owner, resDesc);
    return task;
}
