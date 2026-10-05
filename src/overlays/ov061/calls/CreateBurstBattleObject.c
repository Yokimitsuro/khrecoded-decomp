#include "nitro/types.h"

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
    u16 groupA;
    u8 pad_0a[2];
    u16 groupB;
    u8 pad_0e[0xe];
    s32 scale;
    s32 limit;
    s32 field24;
    s32 field28;
    u8 pad_2c[8];
} TargetSet;

typedef struct {
    int resourceId;
    u32 animationName;
    s32 slotCount;
    u32 modelName;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct {
    u8 pad_00[0x20];
    void (*draw)();
    void (*cleanup)();
    void (*update)();
    void (*onEvent)();
    u8 pad_30[8];
    void (*onStart)();
    void (*onAction)();
    TargetSet targets;
    u16 *groupALink;
    u8 pad_78[4];
    u16 *groupBLink;
    s8 slotA;
    s8 slotB;
    u8 pad_82[2];
    void *messages;
    u8 pad_88[4];
    void *cameraPath;
} BattleObject;

extern char sOv061_CmRB_020d8540[];
extern char sOv061_BaEfFnBrP2_020d8548[];
extern char sOv061_BaChFormatSCiBZ_020d8558[];
extern char *gSoundCategoryNames[];

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void CameraPath_Load(void *path, const char *name);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void InitScriptTask(BattleObject *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ResetTargetSet(TargetSet *set);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern int func_ov021_020a89c8(EntryGroupDesc *desc);
extern u8 *GetOverlaySelectionRecord(u32 player);
extern void OS_SPrintf(char *dst, const char *fmt, ...);
extern void *func_0202c4a0(const char *name, u32 mode);
extern void BuildNodeRecords(BattleObject *obj, ObjectOwner *owner, void *resDesc, void *file);
extern void AcquireEntryHandles(BattleObject *obj, ObjectOwner *owner, void *resDesc);
extern void LoadResGroupHandles(BattleObject *obj, ObjectOwner *owner, void *resDesc);
extern void BeginGuardIntroScene();
extern void func_ov061_020d81b4();
extern void StopEntrySounds();
extern void UpdateTimedBurstAction();

BattleObject *CreateBurstBattleObject(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
{
    BattleObject *obj = NNSi_FndAllocFromDefaultHeap(sizeof(BattleObject));
    u32 targetId;
    TargetSet *targets;
    void *file;
    u32 selection;
    EntryGroupDesc group;
    char path[128];

    obj->cameraPath = NNSi_FndAllocFromDefaultHeap(0x60);
    CameraPath_Load(obj->cameraPath, sOv061_CmRB_020d8540);
    MI_CpuFill8(obj, 0, 0x84);
    obj->slotA = -1;
    obj->slotB = -1;
    InitScriptTask(obj, 4, desc->id, desc->arg);
    obj->messages = Msg_OpenContainerAndReadHeader(sOv061_BaEfFnBrP2_020d8548, owner->player + 8, FALSE);
    targets = &obj->targets;
    targetId = *desc->target;
    ResetTargetSet(targets);
    obj->targets.count = 1;
    targets->ids = NNSi_FndAllocFromDefaultHeap(obj->targets.count * 4);
    targets->ids[0] = targetId;
    targets->field28 = 0;
    targets->field24 = 0;
    targets->scale = 0x1000;
    ZeroBytes0x14(&group);
    group.modelName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000002;
    group.animationName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000003;
    group.slotCount = 2;
    targets->groupA = func_ov021_020a89c8(&group);
    obj->groupALink = &targets->groupA;
    ZeroBytes0x14(&group);
    group.modelName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000000;
    group.animationName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000001;
    group.slotCount = 2;
    targets->groupB = func_ov021_020a89c8(&group);
    obj->groupBLink = &targets->groupB;
    obj->onStart = BeginGuardIntroScene;
    obj->draw = func_ov061_020d81b4;
    obj->onEvent = StopEntrySounds;
    obj->onAction = UpdateTimedBurstAction;
    selection = *GetOverlaySelectionRecord(owner->player);
    OS_SPrintf(path, sOv061_BaChFormatSCiBZ_020d8558, gSoundCategoryNames[selection]);
    file = func_0202c4a0(path, 0x11);
    BuildNodeRecords(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap(file);
    AcquireEntryHandles(obj, owner, resDesc);
    LoadResGroupHandles(obj, owner, resDesc);
    return obj;
}
