#include "nitro/types.h"

typedef struct MenuPanel {
    u8 pad_00000[0x10];
    void *buffer10;
    void *buffer14;
    void *container;
    u8 pad_0001C[0x18];
    u8 unk_34[0x6c0];
    u8 model[0x4768];
    void *unk_4E5C;
    u8 pad_04E60[0xcda0];
    void *heapBlock;
} MenuPanel;

extern BOOL ReleaseRecordSlot(s32 slot);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int ZeroHalfThenFree(void *block);
extern void ReleaseResourceAndDetach(u8 *object);
extern void func_ov076_020ccf30(void *object);
extern void DestroyAllContainerElements(void *container);
extern void ReleaseIfMarked(void *container);
extern void FreePointerIfSet(void **ptr);
extern void SetSecondaryElementEnabled(BOOL enabled);

void MenuPanel_Destroy(MenuPanel *panel)
{
    void *container = panel->container;

    ReleaseRecordSlot(1);
    ReleaseRecordSlot(0);
    NNSi_FndFreeFromDefaultHeap(panel->heapBlock);
    ZeroHalfThenFree(panel->buffer14);
    ZeroHalfThenFree(panel->buffer10);
    ReleaseResourceAndDetach(panel->model);
    func_ov076_020ccf30(panel->unk_34);
    DestroyAllContainerElements(container);
    ReleaseIfMarked(container);
    FreePointerIfSet(&panel->unk_4E5C);
    SetSecondaryElementEnabled(TRUE);
}
