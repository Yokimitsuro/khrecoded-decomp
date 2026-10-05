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

extern char sOv068_BaEfFnSrP2_020d86a0[];
extern char sOv068_BaChFormatSCiBZ_020d86b0[];
extern char sOv068_CmSR_020d86c0[];
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
extern void LoadManagerSpriteSlots(void);
extern void LoadResGroupHandles(BossObject *obj, ObjectOwner *owner, void *resDesc);
extern void func_ov068_020d8120();
extern void StartOv068BossIntro();
extern void RunOv068BossState();
extern void EndOv068BossIntro();

BossObject *CreateOv068BossObject(ObjectOwner *owner, void *resDesc, ObjectDesc *desc)
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
    obj->targets.count = 3;
    targets->ids = NNSi_FndAllocFromDefaultHeap(obj->targets.count * 4);
    targets->ids[0] = 0x319c;
    targets->ids[1] = 0x319d;
    targets->ids[2] = 0x319e;
    obj->messages = Msg_OpenContainerAndReadHeader(sOv068_BaEfFnSrP2_020d86a0, owner->player + 8, FALSE);
    key = (u32)obj->messages;
    ZeroBytes0x14(&group);
    key = (key + 0x8000 & 0xfffffc) << 7;
    group.startKey = key | 0x80000000;
    group.endKey = key | 0x80000001;
    group.param = 3;
    targets->groupB = func_ov021_020a89c8(&group);
    obj->onStart = StartOv068BossIntro;
    obj->draw = func_ov068_020d8120;
    obj->finish = EndOv068BossIntro;
    obj->onAction = RunOv068BossState;
    selection = *GetOverlaySelectionRecord(owner->player);
    OS_SPrintf(path, sOv068_BaChFormatSCiBZ_020d86b0, gSoundCategoryNames[selection]);
    file = func_0202c4a0(path, 0x11);
    BuildNodeRecords(obj, owner, resDesc, file);
    NNSi_FndFreeFromDefaultHeap(file);
    AcquireEntryHandles(obj, owner, resDesc);
    LoadResGroupHandles(obj, owner, resDesc);
    LoadManagerSpriteSlots();
    CameraPath_Load(obj->cameraPath, sOv068_CmSR_020d86c0);
    return obj;
}
