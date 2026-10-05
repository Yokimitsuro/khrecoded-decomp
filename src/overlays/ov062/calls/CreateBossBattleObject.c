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
    u8 pad_08[0x14];
    s32 scale;
    u8 pad_20[4];
    s32 field24;
    s32 field28;
    u8 pad_2c[0x14];
} TargetSet;

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
    s8 slotA;
    s8 slotB;
    u8 pad_82[2];
    void *model;
    void *messages;
    u8 pad_8c[4];
    void *cameraPath;
} BattleObject;

extern char sOv062_CmEB_020d8540[];
extern char sOv062_BaEfFnEbP2_020d8548[];
extern char sOv062_BaChFormatSCiBZ_020d8558[];
extern char *gSoundCategoryNames[];

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void CameraPath_Load(void *path, const char *name);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void InitScriptTask(BattleObject *task, int script, int id, void *arg);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void ResetTargetSet(TargetSet *set);
extern void InitObjWithCallback(void *obj, u32 player, u32 arg);
extern void func_ov062_020d8180(ObjectOwner *owner, BattleObject *obj);
extern u8 *GetOverlaySelectionRecord(u32 player);
extern void OS_SPrintf(char *dst, const char *fmt, ...);
extern void *func_0202c4a0(const char *name, u32 mode);
extern void BuildNodeRecords(BattleObject *obj, ObjectOwner *owner, void *resDesc, void *file);
extern void AcquireEntryHandles(BattleObject *obj, ObjectOwner *owner, void *resDesc);
extern void LoadResGroupHandles(BattleObject *obj, ObjectOwner *owner, void *resDesc);
extern void func_ov062_020d8120();
extern void func_ov062_020d8154();
extern void ForwardTargetHandle();
extern void ForwardTargetHandleValue();
extern void ForwardTargetHandle_020d3b60();
extern void UpdateFinishingAttackAction();

BattleObject *CreateBossBattleObject(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
{
    BattleObject *obj = NNSi_FndAllocFromDefaultHeap(sizeof(BattleObject));
    u32 targetId;
    TargetSet *targets;
    void *file;
    u32 selection;
    char path[128];

    obj->cameraPath = NNSi_FndAllocFromDefaultHeap(0x60);
    CameraPath_Load(obj->cameraPath, sOv062_CmEB_020d8540);
    MI_CpuFill8(obj, 0, 0x84);
    obj->slotA = -1;
    obj->slotB = -1;
    InitScriptTask(obj, 4, desc->id, desc->arg);
    obj->messages = Msg_OpenContainerAndReadHeader(sOv062_BaEfFnEbP2_020d8548, owner->player + 8, FALSE);
    targets = &obj->targets;
    targetId = *desc->target;
    ResetTargetSet(targets);
    obj->targets.count = 1;
    targets->ids = NNSi_FndAllocFromDefaultHeap(obj->targets.count * 4);
    targets->ids[0] = targetId;
    targets->field28 = 0;
    targets->field24 = 0;
    targets->scale = 0x1000;
    obj->onStart = func_ov062_020d8120;
    obj->draw = func_ov062_020d8154;
    obj->update = ForwardTargetHandle;
    obj->cleanup = ForwardTargetHandleValue;
    obj->onEvent = ForwardTargetHandle_020d3b60;
    obj->onAction = UpdateFinishingAttackAction;
    obj->model = NNSi_FndAllocFromDefaultHeap(0x3c);
    InitObjWithCallback(obj->model, owner->player, 1);
    func_ov062_020d8180(owner, obj);
    selection = *GetOverlaySelectionRecord(owner->player);
    OS_SPrintf(path, sOv062_BaChFormatSCiBZ_020d8558, gSoundCategoryNames[selection]);
    file = func_0202c4a0(path, 0x11);
    BuildNodeRecords(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap(file);
    AcquireEntryHandles(obj, owner, resDesc);
    LoadResGroupHandles(obj, owner, resDesc);
    return obj;
}
