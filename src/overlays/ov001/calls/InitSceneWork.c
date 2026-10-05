#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LinkedList {
    void *head;
    void *tail;
} LinkedList;

typedef struct Selection {
    u8 pad_00[4];
    s32 index;
    s32 unk_08;
} Selection;

typedef struct SceneWork {
    u32 unk_00;
    LinkedList list;
    u8 pad_0c[0x20];
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u8 pad_38[4];
    Selection selection;
    fx32 unk_48;
    fx32 unk_4C;
    u8 unk_50[0x7c];
    u8 unk_CC[1];
} SceneWork;

extern SceneWork *data_ov001_020a04a4;
extern u8 sOv001_BaEfTaPZ_0209eb4c[];
extern SceneWork *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov001_0206b930(LinkedList *list);
extern void *SND_RegisterSeq(int a, int b);
extern void func_0202c6a4(int arg0);
extern void *AcquireOrRefreshResourceBlock(void *info, void *textureHeader, int flag);
extern int IndexedPointer_GetFirstWord(void *objectBase, int recordIndex);
extern int ReleaseSharedRecordSlot(void *slot);
extern void InitSpritePairFromResource(void *target, void *objectBase);
extern void InitButtonPanelSprites(void *target, void *objectBase);
extern void func_ov001_0206c704(void *callback);
extern void RefreshActiveMenuObjects(void);
extern void UpdateTargetMenuState(void);

void *InitSceneWork(void)
{
    SceneWork *work = NNSi_FndGetCurrentRootHeap();
    Selection *selection;
    void *slot;
    void *objectBase;

    data_ov001_020a04a4 = work;
    work->unk_00 = 0xcc;
    work->unk_2C = 0;
    work->unk_30 = 0;
    work->unk_34 = 0;
    func_ov001_0206b930(&work->list);
    selection = &work->selection;
    selection->unk_08 = 0;
    selection->index = -1;
    work->unk_48 = 0x14000;
    work->unk_4C = 0xa000;
    slot = SND_RegisterSeq((int)sOv001_BaEfTaPZ_0209eb4c, 0x11);
    func_0202c6a4(0);
    objectBase = AcquireOrRefreshResourceBlock(slot, NULL, 1);
    func_0202c6a4(1);
    IndexedPointer_GetFirstWord(objectBase, 7);
    InitSpritePairFromResource(work->unk_50, objectBase);
    InitButtonPanelSprites(work->unk_CC, objectBase);
    ReleaseSharedRecordSlot(slot);
    func_ov001_0206c704(RefreshActiveMenuObjects);
    return UpdateTargetMenuState;
}
