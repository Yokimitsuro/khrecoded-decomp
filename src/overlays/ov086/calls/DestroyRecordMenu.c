#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1dc];
    void *listEntry;
} Ov086Menu;

extern Ov086Menu *data_ov086_020c3020;
extern void *func_ov039_020bc1ec(void);
extern void RemoveListEntry(void *entry);
extern void func_ov027_020b7e1c(void *tracker);
extern void DestroyAllContainerElements(void *container);
extern void ReleaseIfMarked(void *owner);
extern BOOL DestroyFndObjectList(void *list);
extern void FreePointerIfSet(void *ptr);
extern void FreeAllocatedBuffers(void *owner);
extern BOOL ReleaseRecordSlot(s32 slot);
extern void ReleaseRecordManager(void);

void DestroyRecordMenu(void)
{
    void *container = func_ov039_020bc1ec();
    Ov086Menu *menu = data_ov086_020c3020;
    u8 *base = (u8 *)menu;

    RemoveListEntry(menu->listEntry);
    func_ov027_020b7e1c(base + 0x190);
    DestroyAllContainerElements(container);
    ReleaseIfMarked(container);
    DestroyFndObjectList(base + 0xc);
    DestroyFndObjectList(base + 0x40);
    DestroyFndObjectList(base + 0x74);
    FreePointerIfSet(menu);
    FreeAllocatedBuffers(base + 0x174);
    ReleaseRecordSlot(0);
    ReleaseRecordManager();
    *(vu32 *)0x04001000 &= ~0xe000;
}
