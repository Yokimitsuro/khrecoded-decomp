#include "nitro/types.h"

typedef struct SlotPoolConfig {
    u32 imageParams;
    u32 rest[3];
} SlotPoolConfig;

typedef struct {
    u8 pad_000[0x744];
    int entryCount;
} Ov089Menu;

extern SlotPoolConfig data_ov089_020c0520;

extern void *func_ov039_020bc1dc(void);
extern u32 BuildSlotImageParams(int slot, u32 low);
extern void InitObjManagerAndMark(void *container, SlotPoolConfig *config);
extern void func_ov027_020b8fb8(void *container, u32 imageParams, int count);
extern void SetAllElementObjectModes(void *container, int mode);
extern void *FindWidgetById(void *container, int id);
extern void SetFocusedWidget(void *container, void *widget);
extern void SetEntrySlotsVisible(void *container, void *widget, BOOL visible);
extern void SetWidgetRootDpadEnabled(void *container, BOOL enabled);
extern void func_ov027_020b90b8(void *container, void *callback);
extern void func_ov027_020b90a8(void *container, int id, void *callback);
extern void func_ov089_020befe0(void);
extern void func_ov089_020c042c(void);
extern void func_ov089_020c047c(void);
extern void func_ov089_020c04e8(void);

void LoadEntryMenuWidgets(Ov089Menu *menu)
{
    void *container = func_ov039_020bc1dc();
    SlotPoolConfig config = data_ov089_020c0520;

    config.imageParams = BuildSlotImageParams(2, 0x10);
    InitObjManagerAndMark(container, &config);
    func_ov027_020b8fb8(container, BuildSlotImageParams(2, 0x11), 10);
    SetAllElementObjectModes(container, 2);
    SetFocusedWidget(container, FindWidgetById(container, 2));
    if (menu->entryCount <= 1) {
        SetEntrySlotsVisible(container, FindWidgetById(container, 9), FALSE);
    }
    SetWidgetRootDpadEnabled(container, TRUE);
    func_ov027_020b90b8(container, func_ov089_020befe0);
    func_ov027_020b90a8(container, 2, func_ov089_020c042c);
    func_ov027_020b90a8(container, 7, func_ov089_020c047c);
    func_ov027_020b90a8(container, 8, func_ov089_020c04e8);
}
