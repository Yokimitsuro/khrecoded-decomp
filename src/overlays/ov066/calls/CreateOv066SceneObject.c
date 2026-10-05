#include "nitro/types.h"

typedef struct EntryGroupDesc {
    int kind;
    u32 endKey;
    int param;
    u32 startKey;
    int extra;
} EntryGroupDesc;

typedef struct {
    s16 id;
    u8 pad_02[2];
    void *arg;
    u32 *target;
} ObjectDesc;

typedef struct {
    u8 pad_00[0x14];
    u32 player;
} ObjectOwner;

typedef struct {
    s32 count;
    u32 *ids;
    s16 groups[3];
    u8 pad_0e[0x0e];
    s32 scale;
    u8 pad_20[4];
    s32 field24;
    s32 field28;
    u8 pad_2c[8];
} TargetSet;

typedef struct {
    u8 pad_00[0x10];
    void **handles;
    s32 handleCount;
    u8 pad_18[8];
    void (*draw)();
    u8 pad_24[0x14];
    void (*onStart)();
    void (*onAction)();
    TargetSet targets;
    s16 *groupA;
    s16 *groupB;
    s16 *groupC;
    s8 slotA;
    s8 slotB;
    u8 pad_82[2];
    void *messages;
    void *cameraPath;
} SceneObject;

extern char sOv066_CmBZ_020d8780[];
extern char sOv066_BaEfFnBzP2_020d8788[];
extern char sOv066_BaChFormatSCiBZ_020d8798[];
extern char *gSoundCategoryNames[];

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void CameraPath_Load(void *path, const char *name);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void InitScriptTask(SceneObject *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ResetTargetSet(TargetSet *set);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern s16 func_ov021_020a89c8(EntryGroupDesc *desc);
extern u8 *GetOverlaySelectionRecord(u32 player);
extern void OS_SPrintf(char *dst, const char *fmt, ...);
extern void *func_0202c4a0(const char *name, u32 mode);
extern void BuildNodeRecords(SceneObject *obj, ObjectOwner *owner, void *resDesc, void *file);
extern u32 func_ov001_0206dba0(int index);
extern void *AcquireRecordHandle(ObjectOwner *owner, void *resDesc, int id, u32 key);
extern void LoadResGroupHandles(SceneObject *obj, ObjectOwner *owner, void *resDesc);
extern void func_ov066_020d8120();
extern void func_ov066_020d81e8();
extern void UpdateDualMarkerAction();

SceneObject *CreateOv066SceneObject(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
{
    SceneObject *obj = NNSi_FndAllocFromDefaultHeap(sizeof(SceneObject));
    u32 targetId;
    TargetSet *targets;
    EntryGroupDesc group;
    void *file;
    u32 base;
    u32 selection;
    char path[128];

    obj->cameraPath = NNSi_FndAllocFromDefaultHeap(0x60);
    CameraPath_Load(obj->cameraPath, sOv066_CmBZ_020d8780);
    MI_CpuFill8(obj, 0, 0x84);
    obj->slotA = -1;
    obj->slotB = -1;
    InitScriptTask(obj, 4, desc->id, desc->arg);
    obj->messages = Msg_OpenContainerAndReadHeader(sOv066_BaEfFnBzP2_020d8788, owner->player + 8, FALSE);
    targets = &obj->targets;
    targetId = *desc->target;
    ResetTargetSet(targets);
    obj->targets.count = 1;
    targets->ids = NNSi_FndAllocFromDefaultHeap(obj->targets.count * 4);
    targets->ids[0] = 0x16440;
    targets->field28 = 0;
    targets->field24 = 0;
    targets->scale = 0x1000;
    ZeroBytes0x14(&group);
    group.startKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000000;
    group.endKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000001;
    group.param = 1;
    targets->groups[0] = func_ov021_020a89c8(&group);
    obj->groupA = &targets->groups[0];
    ZeroBytes0x14(&group);
    group.startKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000002;
    group.endKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000003;
    group.param = 1;
    targets->groups[1] = func_ov021_020a89c8(&group);
    obj->groupB = &targets->groups[1];
    ZeroBytes0x14(&group);
    group.startKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000004;
    group.endKey = (((u32)obj->messages + 0x8000 & 0xfffffc) << 7) | 0x80000005;
    group.param = 1;
    targets->groups[2] = func_ov021_020a89c8(&group);
    obj->groupC = &targets->groups[2];
    obj->onStart = func_ov066_020d8120;
    obj->draw = func_ov066_020d81e8;
    obj->onAction = UpdateDualMarkerAction;

    selection = *GetOverlaySelectionRecord(owner->player);
    OS_SPrintf(path, sOv066_BaChFormatSCiBZ_020d8798, gSoundCategoryNames[selection]);
    file = func_0202c4a0(path, 0x11);
    BuildNodeRecords(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap(file);
    obj->handleCount = 1;
    obj->handles = NNSi_FndAllocFromDefaultHeap(obj->handleCount * 4);
    base = func_ov001_0206dba0(4);
    obj->handles[0] = AcquireRecordHandle(owner, resDesc, targetId,
        ((base + 0x8000 & 0xfffffc) << 7) | 0x80000000 | (targetId & 0x1ff));
    LoadResGroupHandles(obj, owner, resDesc);
    return obj;
}
