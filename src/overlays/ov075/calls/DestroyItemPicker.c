#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct {
    u8 pad_00000[0x10];
    void *primaryArchive;
    void *secondaryArchive;
    ResourceContainer *layout;
    u8 pad_0001c[0x34 - 0x1c];
    u8 listState[0x6f4 - 0x34];
    u8 model[0x4e5c - 0x6f4];
    void *messageTable;
    u8 pad_04e60[0x11c00 - 0x4e60];
    void *listData;
} ItemPicker;

extern BOOL ReleaseRecordSlot(s32 slot);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int ZeroHalfThenFree(void *arg0);
extern void ReleaseResourceAndDetach(u8 *object);
extern void func_ov075_020d10fc(void *state);
extern void DestroyAllContainerElements(ResourceContainer *container);
extern void ReleaseIfMarked(ResourceContainer *container);
extern void FreePointerIfSet(void **ptr);
extern void SetSecondaryElementEnabled(BOOL enabled);

void DestroyItemPicker(ItemPicker *picker)
{
    ResourceContainer *layout = picker->layout;

    ReleaseRecordSlot(1);
    ReleaseRecordSlot(0);
    NNSi_FndFreeFromDefaultHeap(picker->listData);
    ZeroHalfThenFree(picker->secondaryArchive);
    ZeroHalfThenFree(picker->primaryArchive);
    ReleaseResourceAndDetach(picker->model);
    func_ov075_020d10fc(picker->listState);
    DestroyAllContainerElements(layout);
    ReleaseIfMarked(layout);
    FreePointerIfSet(&picker->messageTable);
    SetSecondaryElementEnabled(TRUE);
}
