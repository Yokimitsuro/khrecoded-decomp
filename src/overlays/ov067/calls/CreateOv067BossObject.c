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
} ObjectDesc;

typedef struct {
    u8 pad_00[0x14];
    u32 player;
} ObjectOwner;

typedef struct {
    s32 count;
    u32 *ids;
    s16 groupA;
    s16 pad_0a;
    s16 groupB;
    s16 pad_0e;
    s32 field10;
    u8 pad_14[8];
    s32 scale;
    s32 range;
    s32 field24;
    s32 field28;
    u8 pad_2c[8];
} TargetSet;

typedef struct {
    u8 pad_00[0x20];
    void (*draw)();
    u8 pad_24[8];
    void (*finish)();
    u8 pad_30[8];
    void (*onStart)();
    void (*onAction)();
    TargetSet targets;
    s16 *groupAPtr;
    u8 pad_78[4];
    s16 *groupBPtr;
    s8 slotA;
    s8 slotB;
    u8 pad_82[2];
    u8 cameraPath[0x6c];
    void *messages;
    int introActive;
} BossObject;

extern char data_ov067_020d8560[];
extern char data_ov067_020d8570[];
extern char data_ov067_020d8580[];
extern char *gSoundCategoryNames[];

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void CameraPath_Load(void *path, const char *name);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void InitScriptTask(BossObject *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ResetTargetSet(TargetSet *set);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern s16 func_ov021_020a89c8(EntryGroupDesc *desc);
extern u8 *GetOverlaySelectionRecord(u32 player);
extern void OS_SPrintf(char *dst, const char *fmt, ...);
extern void *func_0202c4a0(const char *name, u32 mode);
extern void BuildNodeRecords(BossObject *obj, ObjectOwner *owner, void *resDesc, void *file);
extern void AcquireEntryHandles(BossObject *obj, ObjectOwner *owner, void *resDesc);
extern void LoadResGroupHandles(BossObject *obj, ObjectOwner *owner, void *resDesc);
extern void func_ov067_020d8120();
extern void StartOv067BossIntro();
extern void RunOv067BossIntroState();
extern void EndOv067BossIntro();

BossObject *CreateOv067BossObject(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
{
    BossObject *obj = NNSi_FndAllocFromDefaultHeap(sizeof(BossObject));
    TargetSet *targets;
    u32 key;
    EntryGroupDesc group;
    void *file;
    u32 selection;
    char path[128];

    MI_CpuFill8(obj, 0, 0x84);
    obj->slotA = -1;
    obj->slotB = -1;
    InitScriptTask(obj, 4, desc->id, desc->arg);
    targets = &obj->targets;
    ResetTargetSet(targets);
    obj->targets.count = 1;
    targets->ids = NNSi_FndAllocFromDefaultHeap(obj->targets.count * 4);
    targets->ids[0] = 0x332c;
    targets->scale = 0x12000;
    targets->range = 0x7fffffff;
    targets->field24 = 0;
    targets->field28 = 0;
    obj->messages = Msg_OpenContainerAndReadHeader(data_ov067_020d8560, owner->player + 8, FALSE);
    key = (u32)obj->messages;
    ZeroBytes0x14(&group);
    key = (key + 0x8000 & 0xfffffc) << 7;
    group.startKey = key | 0x80000000;
    group.endKey = key | 0x80000001;
    group.param = 1;
    targets->groupB = func_ov021_020a89c8(&group);
    obj->groupBPtr = &targets->groupB;
    ZeroBytes0x14(&group);
    group.startKey = key | 0x80000002;
    group.endKey = key | 0x80000003;
    group.param = 8;
    targets->groupA = func_ov021_020a89c8(&group);
    targets->field10 = 0;
    obj->groupAPtr = &targets->groupA;
    obj->onStart = StartOv067BossIntro;
    obj->draw = func_ov067_020d8120;
    obj->finish = EndOv067BossIntro;
    obj->onAction = RunOv067BossIntroState;
    selection = *GetOverlaySelectionRecord(owner->player);
    OS_SPrintf(path, data_ov067_020d8570, gSoundCategoryNames[selection]);
    file = func_0202c4a0(path, 0x11);
    BuildNodeRecords(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap(file);
    AcquireEntryHandles(obj, owner, resDesc);
    LoadResGroupHandles(obj, owner, resDesc);
    obj->introActive = 0;
    CameraPath_Load(obj->cameraPath, data_ov067_020d8580);
    return obj;
}
