#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MenuAnimSlot {
    int slot;
    int sequence;
} MenuAnimSlot;

typedef struct MapMenu {
    u8 pad_00[0xc];
    s32 archiveBase;
    u8 pad_10[0x10];
    BOOL active;
    u8 pad_24[0x10];
    BOOL visible;
    u8 pad_38[0x10];
    s32 scrollX;
    s32 scrollY;
    u8 pad_50[0x8];
    u8 renderer[0x6434];
    s32 markerSlot;
    s32 frameSlot;
    u8 pad_6494[0x10];
    MenuAnimSlot cursor;
    u8 pad_64AC[0x1afc];
    fx32 position;
} MapMenu;

extern MapMenu *data_ov023_020b6f84;

extern void SetSlotAnimSequence(void *owner, int slot, int sequence);
extern void IndexedRecords_SetFlag2(void *owner, int slot, int value);
extern void func_0204f0d4(void *owner, int slot);
extern int PXI_Init_0204f0c8(void *owner, int sequence, int mode);
extern void Slot_SetMode2Bit(void *owner, int slot, int value);
extern void *QueueFileLoadRequest(u32 archiveId, int loadMode, void (*callback)(void *), void *userData);
extern void LoadMenuScreenResource(void *resource);

void ResetMapMenuScreen(void)
{
    MapMenu *menu = data_ov023_020b6f84;
    void *renderer = menu->renderer;

    SetSlotAnimSequence(renderer, menu->markerSlot, 0x1d);
    IndexedRecords_SetFlag2(renderer, menu->frameSlot, 0);
    func_0204f0d4(renderer, menu->cursor.slot);
    menu->cursor.slot = PXI_Init_0204f0c8(menu->renderer, 0, 1);
    menu->cursor.sequence = 0;
    Slot_SetMode2Bit(menu->renderer, menu->cursor.slot, 3);
    menu->active = TRUE;
    menu->scrollX = 0;
    menu->scrollY = 0;
    menu->position = 0x21000;
    menu->visible = TRUE;
    QueueFileLoadRequest(((menu->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (0x90 & 0x1ff),
                                  1, LoadMenuScreenResource, NULL);
}
