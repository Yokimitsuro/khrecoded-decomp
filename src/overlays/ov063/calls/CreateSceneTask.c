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
} TaskOwner;

typedef struct {
    int resourceId;
    u32 animationName;
    s32 slotCount;
    u32 modelName;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct {
    u8 pad_00[0x10];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*draw)();
    void (*cleanup)();
    void (*update)();
    u8 pad_2c[4];
    void (*onEvent)();
    u8 pad_34[4];
    void (*onStart)();
    void (*onAction)();
    u32 resourceId;
    u8 pad_44[0xc];
    u16 groupA;
    u16 groupB;
    void *messages;
    void *model;
    void *cameraPath;
} SceneTask;

extern char sOv063_CmHo_020d8720[];
extern char sOv063_BaEfFnHlP2_020d8728[];

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void CameraPath_Load(void *path, const char *name);
extern void InitScriptTask(SceneTask *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern int func_ov021_020a89c8(EntryGroupDesc *desc);
extern void InitObjWithCallback(void *obj, u32 player, u32 arg);
extern void SetupUnitEffectModel(TaskOwner *owner, SceneTask *task);
extern u32 func_ov001_0206dba0(int index);
extern void *AcquireRecordHandle(TaskOwner *owner, void *resDesc, u32 id, u32 key);
extern void LoadResGroupHandles(SceneTask *task, TaskOwner *owner, void *resDesc);
extern void func_ov063_020d81ac();
extern void BeginBossIntroScene();
extern void func_ov063_020d817c();
extern void func_ov063_020d81a0();
extern void func_ov063_020d81b8();
extern void UpdateGroundSlamAction();

SceneTask *CreateSceneTask(TaskOwner *owner, void *resDesc, TaskDesc *desc)
{
    SceneTask *task = NNSi_FndAllocFromDefaultHeap(sizeof(SceneTask));
    EntryGroupDesc group;
    u32 high;
    void *messages;
    u32 base;

    task->cameraPath = NNSi_FndAllocFromDefaultHeap(0x60);
    CameraPath_Load(task->cameraPath, sOv063_CmHo_020d8720);
    InitScriptTask(task, 4, desc->id, desc->arg);
    task->update = func_ov063_020d81ac;
    task->onStart = BeginBossIntroScene;
    task->draw = func_ov063_020d817c;
    task->cleanup = func_ov063_020d81a0;
    task->onEvent = func_ov063_020d81b8;
    task->onAction = UpdateGroundSlamAction;
    messages = Msg_OpenContainerAndReadHeader(sOv063_BaEfFnHlP2_020d8728, owner->player + 8, FALSE);
    task->messages = messages;
    ZeroBytes0x14(&group);
    high = (((u32)messages + 0x8000) & 0xfffffc) << 7;
    group.modelName = high | 0x80000000;
    group.animationName = high | 0x80000001;
    group.slotCount = 1;
    task->groupA = func_ov021_020a89c8(&group);
    ZeroBytes0x14(&group);
    group.modelName = high | 0x80000002;
    group.animationName = high | 0x80000003;
    group.slotCount = 2;
    task->groupB = func_ov021_020a89c8(&group);
    task->model = NNSi_FndAllocFromDefaultHeap(0x3c);
    InitObjWithCallback(task->model, owner->player, 1);
    SetupUnitEffectModel(owner, task);
    task->resourceId = *desc->resource;
    task->handleCount = 1;
    task->handles = NNSi_FndAllocFromDefaultHeap(task->handleCount * 4);
    base = func_ov001_0206dba0(4);
    task->handles[0] = AcquireRecordHandle(owner, resDesc, task->resourceId,
        ((((base + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (task->resourceId & 0x1ff));
    LoadResGroupHandles(task, owner, resDesc);
    return task;
}
