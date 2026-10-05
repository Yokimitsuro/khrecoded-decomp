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
    u8 pad_2c[4];
    void (*onEvent)();
    u8 pad_34[4];
    void (*onStart)();
    void (*onAction)();
    TargetSet targets;
    u16 *groupALink;
    u8 pad_78[4];
    u16 *groupBLink;
    s8 slotA;
    s8 slotB;
    u8 pad_82[2];
    void *model;
    void *messages;
    u8 pad_8c[0x10];
    void *cameraPath;
} BattleObject;

extern char sOv065_CmMR_020d8600[];
extern char sOv065_BaEfFnMrP2_020d8608[];
extern char sOv065_BaChFormatSCiBZ_020d8618[];
extern char *gSoundCategoryNames[];

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void CameraPath_Load(void *path, const char *name);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void InitScriptTask(BattleObject *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ResetTargetSet(TargetSet *set);
extern void InitObjWithCallback(void *obj, u32 player, u32 arg);
extern void func_ov065_020d82d0(ObjectOwner *owner, BattleObject *obj);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern int func_ov021_020a89c8(EntryGroupDesc *desc);
extern u8 *GetOverlaySelectionRecord(u32 player);
extern void OS_SPrintf(char *dst, const char *fmt, ...);
extern void *func_0202c4a0(const char *name, u32 mode);
extern void BuildNodeRecords(BattleObject *obj, ObjectOwner *owner, void *resDesc, void *file);
extern void AcquireEntryHandles(BattleObject *obj, ObjectOwner *owner, void *resDesc);
extern void LoadResGroupHandles(BattleObject *obj, ObjectOwner *owner, void *resDesc);
extern void func_ov065_020d8120();
extern void func_ov065_020d8154();
extern void ForwardTargetHandle();
extern void ForwardTargetHandleValue();
extern void ForwardTargetHandle_020d3b60();
extern void UpdateAuraAttackAction();

BattleObject *CreateAuraBattleObject(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
{
    BattleObject *obj = NNSi_FndAllocFromDefaultHeap(sizeof(BattleObject));
    u32 targetId;
    TargetSet *targets;
    void *file;
    u32 selection;
    EntryGroupDesc group;
    char path[128];

    obj->cameraPath = NNSi_FndAllocFromDefaultHeap(0x60);
    CameraPath_Load(obj->cameraPath, sOv065_CmMR_020d8600);
    MI_CpuFill8(obj, 0, 0x84);
    obj->slotA = -1;
    obj->slotB = -1;
    InitScriptTask(obj, 4, desc->id, desc->arg);
    obj->messages = Msg_OpenContainerAndReadHeader(sOv065_BaEfFnMrP2_020d8608, owner->player + 8, FALSE);
    targets = &obj->targets;
    targetId = *desc->target;
    ResetTargetSet(targets);
    obj->targets.count = 1;
    targets->ids = NNSi_FndAllocFromDefaultHeap(obj->targets.count * 4);
    targets->ids[0] = targetId;
    targets->field28 = 0;
    targets->field24 = 0;
    targets->scale = 0x1f000;
    targets->limit = 0x7fffffff;
    ZeroBytes0x14(&group);
    group.modelName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000000;
    group.animationName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000001;
    group.slotCount = 1;
    targets->groupB = func_ov021_020a89c8(&group);
    obj->groupBLink = &targets->groupB;
    group.modelName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000002;
    group.animationName = ((((u32)obj->messages + 0x8000) & 0xfffffc) << 7) | 0x80000003;
    group.slotCount = 1;
    targets->groupA = func_ov021_020a89c8(&group);
    obj->groupALink = &targets->groupA;
    obj->onStart = func_ov065_020d8120;
    obj->draw = func_ov065_020d8154;
    obj->update = ForwardTargetHandle;
    obj->cleanup = ForwardTargetHandleValue;
    obj->onEvent = ForwardTargetHandle_020d3b60;
    obj->onAction = UpdateAuraAttackAction;
    obj->model = NNSi_FndAllocFromDefaultHeap(0x3c);
    InitObjWithCallback(obj->model, owner->player, 1);
    func_ov065_020d82d0(owner, obj);
    selection = *GetOverlaySelectionRecord(owner->player);
    OS_SPrintf(path, sOv065_BaChFormatSCiBZ_020d8618, gSoundCategoryNames[selection]);
    file = func_0202c4a0(path, 0x11);
    BuildNodeRecords(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap(file);
    AcquireEntryHandles(obj, owner, resDesc);
    LoadResGroupHandles(obj, owner, resDesc);
    return obj;
}
