#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 pad_001[0x4b3];
} SceneEntry;

typedef struct {
    u32 unk_00;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u32 flags;
    u8 unk_0c;
    u8 pad_0d[3];
    u8 mode;
    u8 subMode;
    u8 pad_12[2];
    SceneEntry *entries;
    u8 slotCount;
    u8 extraCount;
    u8 memberCount;
    u8 unk_1b;
    u16 entrySize;
    u8 pad_01e[0x32a];
    u8 levelA;
    u8 levelB;
    u8 pad_34a[0x1f2];
    u8 embedded[0x1dd8];
    void *file;
    u8 pad_2318[0x10];
    u32 scale;
} Scene;

typedef struct {
    u8 pad_00[0x3e];
    u8 kind;
} Member;

typedef struct {
    u8 subMode;
    u8 mode;
    u8 pad_02[2];
    u8 *options;
    Member *members[9];
} SceneSetup;

typedef struct {
    int order[9];
} MemberOrder;

typedef struct {
    s16 kind;
} PlayerFlagRecord;

typedef struct {
    s16 kind;
    u8 pad_02[10];
} SelectionItem;

typedef struct {
    u8 pad_000[0x2c];
    SelectionItem items[21];
    u8 pad_128[4];
    int itemCount;
} SelectionRecord;

extern char sOv041_RpgEnpPP_020cf93c[];
extern MemberOrder data_ov041_020cf6b8;
extern void NNS_GfdDumpFrmTexVramManager(void);
extern void NNS_GfdDumpFrmPlttVramManager(void);
extern void PushVramState(void);
extern void ReleaseSeqArcHeapLevel(int level);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(int value, void *dst, u32 size);
extern void *func_0202c4a0(const char *path, int kind);
extern BOOL func_ov001_020645c8(int id);
extern void func_ov001_020645e8(int id);
extern void func_ov041_020c0960(int slot, int kind);
extern void func_ov041_020c09ec(int slot, Member *member, int index);
extern void func_ov041_020be088(void);
extern void func_ov041_020bda88(void);
extern void func_ov041_020bdc8c(void);
extern void func_ov041_020c0c14(u8 slot, u8 subMode);
extern void func_ov041_020c3678(u8 slot);
extern PlayerFlagRecord *GetPlayerFlagRecord(int index);
extern void SetMenuEntryHighlight(int menu, int index, int highlighted);
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern void InitRecordOwnerSlots(void *object);
extern void func_ov041_020bf0c0(void);
extern BOOL IsStageKindAvailable(int id);
extern void QueueSoundCommandForArc(int sound);
extern void SelectFieldMenuPage(int page);
extern void RequestFieldRefresh(void);
extern void func_ov001_0207d148(int value);
extern void func_ov041_020bd760(int value);

void InitMenuScene(Scene **scenePtr, SceneSetup *setup) {
    Scene *scene;
    MemberOrder memberOrder;
    int i;
    int slot;
    u8 level;

    NNS_GfdDumpFrmTexVramManager();
    NNS_GfdDumpFrmPlttVramManager();
    PushVramState();
    ReleaseSeqArcHeapLevel(2);
    scene = NNSi_FndAllocFromDefaultHeap(sizeof(Scene));
    *scenePtr = scene;
    MIi_CpuClearFast(0, scene, sizeof(Scene));
    scene->unk_06 = 0;
    scene->unk_00 = 0;
    scene->unk_04 = 0;
    scene->unk_07 = 0;
    scene->flags = 0;
    scene->unk_0c = 0;
    scene->entries = NULL;
    scene->slotCount = 0;
    scene->extraCount = 1;
    scene->memberCount = 0;
    scene->unk_1b = 0;
    scene->entrySize = 0;
    scene->scale = 0x1000;
    scene->mode = setup->mode;
    scene->subMode = setup->subMode;
    scene->file = func_0202c4a0(sOv041_RpgEnpPP_020cf93c, 0x12);
    if (func_ov001_020645c8(0x3726)) {
        scene->flags |= 8;
        func_ov001_020645e8(0x3726);
    }
    for (i = 0; i < 9; i++) {
        if (setup->members[i] == NULL) {
            continue;
        }
        switch (setup->members[i]->kind) {
        case 0x16:
            scene->flags |= 0x40;
            scene->flags |= 0x20;
            scene->flags |= 8;
            scene->flags |= 0x200000;
            break;
        case 0x18:
            scene->flags |= 0x40;
            scene->flags |= 0x20;
            scene->flags |= 8;
            scene->flags |= 0x800000;
            break;
        case 0x19:
            scene->flags |= 0x40;
            scene->flags |= 0x20;
            scene->flags |= 8;
            scene->flags |= 0x2000000;
            break;
        case 0x1a:
            scene->flags |= 0x40;
            scene->flags |= 0x20;
            scene->flags |= 8;
            scene->flags |= 0x1000000;
            break;
        case 0x63:
            scene->flags |= 0x20;
            scene->flags |= 8;
            scene->flags |= 0x100000;
            break;
        case 0x17:
            scene->flags |= 0x20;
            scene->flags |= 8;
            scene->flags |= 0x80;
            scene->flags |= 0x400000;
            break;
        }
    }
    if (scene->flags & 0x2200000) {
        level = 2;
    } else if (scene->flags & 0x1800000) {
        level = 3;
    } else {
        level = 0;
    }
    scene->levelA = level;
    scene->levelB = level;
    if (*setup->options & 1) {
        scene->extraCount++;
    }
    if (*setup->options & 2) {
        scene->extraCount++;
    }
    for (i = 0; i < 9; i++) {
        if (setup->members[i] != NULL) {
            scene->memberCount++;
        }
    }
    scene->slotCount = scene->extraCount + scene->memberCount;
    scene->entrySize = sizeof(SceneEntry);
    scene->entries = NNSi_FndAllocFromDefaultHeap(scene->entrySize * scene->slotCount);
    MIi_CpuClearFast(0, scene->entries, scene->entrySize * scene->slotCount);
    slot = 0;
    func_ov041_020c0960(0, 0xff);
    if (*setup->options & 1) {
        scene->flags |= 0x800;
        slot++;
        func_ov041_020c0960((u8)slot, 0xfe);
    }
    if (*setup->options & 2) {
        scene->flags |= 0x400;
        slot++;
        func_ov041_020c0960((u8)slot, 0xfd);
    }
    memberOrder = data_ov041_020cf6b8;
    for (i = 0; i < 9; i++) {
        if (setup->members[memberOrder.order[i]] != NULL) {
            slot++;
            func_ov041_020c09ec((u8)slot, setup->members[memberOrder.order[i]], (u8)i);
        }
    }
    func_ov041_020be088();
    func_ov041_020bda88();
    func_ov041_020bdc8c();
    if (scene->flags & 0x20) {
        scene->subMode = 1;
    }
    if (scene->subMode != 1) {
        scene->flags |= 2;
    }
    for (i = 0; i < scene->slotCount; i++) {
        func_ov041_020c0c14(i, scene->subMode);
        if ((scene->flags & 0x80) && scene->entries[i].kind == 0) {
            func_ov041_020c3678(i);
        }
    }
    for (i = 0; i < 8; i++) {
        if (GetPlayerFlagRecord(i) != NULL) {
            switch (GetPlayerFlagRecord(i)->kind) {
            case 0xd0:
            case 0xd1:
            case 0xd2:
                SetMenuEntryHighlight(1, i, 0);
                break;
            case 0xd3:
                if (scene->flags & 8) {
                    SetMenuEntryHighlight(1, i, 0);
                } else {
                    SetMenuEntryHighlight(1, i, 1);
                }
                break;
            default:
                SetMenuEntryHighlight(1, i, 1);
                break;
            }
        }
    }
    for (i = 0; i < GetOverlaySelectionRecord(0)->itemCount; i++) {
        switch (GetOverlaySelectionRecord(0)->items[i].kind) {
        case 0xb9:
        case 0xba:
        case 0xbb:
        case 0xbc:
        case 0xbd:
            SetMenuEntryHighlight(0, i, 0);
            break;
        default:
            SetMenuEntryHighlight(0, i, 1);
            break;
        }
    }
    InitRecordOwnerSlots(scene->embedded);
    func_ov041_020bf0c0();
    if (IsStageKindAvailable(0x18)) {
        QueueSoundCommandForArc(0xb2);
    }
    if (IsStageKindAvailable(0x19)) {
        QueueSoundCommandForArc(0xb3);
    }
    SelectFieldMenuPage(0);
    RequestFieldRefresh();
    func_ov001_0207d148(0x80);
    func_ov041_020bd760(0x1000);
    NNS_GfdDumpFrmTexVramManager();
    NNS_GfdDumpFrmPlttVramManager();
}
