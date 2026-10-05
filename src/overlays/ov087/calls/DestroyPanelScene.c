#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ObjectList;

typedef struct {
    u32 id;
    u8 model[0x104];
} ListEntry;

typedef struct {
    u8 pad_000[0x8];
    int entryCount;
    u8 pad_00C[0x8];
    u8 headerModel[0x104];
    ListEntry entries[8];
    u8 pad_958[0x38];
    ObjectList cursorList;
    ObjectList frameList;
    ObjectList slotLists[3];
    ObjectList tabLists[2];
    ObjectList labelList;
    ObjectList iconList;
    void *workBuffer;
} PanelScene;

extern void ReleaseResourceAndDetach(u8 *object);
extern void *func_ov039_020bc1ac(void);
extern void func_ov027_020b7fac(void *ctx, int arg);
extern void *func_ov039_020bc1dc(void);
extern void DestroyAllContainerElements(void *container);
extern void ReleaseIfMarked(void *container);
extern void func_ov027_020b90b8(void *container, u32 value);
extern void FreePointerIfSet(void **ptr);
extern BOOL DestroyFndObjectList(ObjectList *list);
extern BOOL ReleaseRecordSlot(s32 slot);
extern void func_ov087_020c64f8(void);
extern void SetSecondaryElementEnabled(BOOL enabled);

void DestroyPanelScene(PanelScene *scene)
{
    int index;

    ReleaseResourceAndDetach(scene->headerModel);
    for (index = 0; index < scene->entryCount; index++) {
        ReleaseResourceAndDetach(scene->entries[index].model);
    }
    func_ov027_020b7fac(func_ov039_020bc1ac(), 0);
    DestroyAllContainerElements(func_ov039_020bc1dc());
    ReleaseIfMarked(func_ov039_020bc1dc());
    func_ov027_020b90b8(func_ov039_020bc1dc(), 0);
    FreePointerIfSet(&scene->workBuffer);
    DestroyFndObjectList(&scene->iconList);
    DestroyFndObjectList(&scene->labelList);
    DestroyFndObjectList(&scene->frameList);
    DestroyFndObjectList(&scene->cursorList);
    for (index = 0; index < 3; index++) {
        DestroyFndObjectList(&scene->slotLists[index]);
    }
    for (index = 0; index < 2; index++) {
        DestroyFndObjectList(&scene->tabLists[index]);
    }
    ReleaseRecordSlot(2);
    func_ov087_020c64f8();
    SetSecondaryElementEnabled(TRUE);
}
