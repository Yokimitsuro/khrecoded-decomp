#include "nitro/types.h"

typedef struct SlotItem {
    s32 x;
    s32 y;
    s32 enabled;
    s32 spriteId;
    s32 paletteId;
    s32 handle;
} SlotItem;

typedef struct SlotView {
    SlotItem items[18];
} SlotView;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x11edc];
    s32 markerHidden;
    u8 pad_11EE4[0x1b914 - 0x11ee4];
    SlotView slots[8];
    SlotItem extras[4];
} SlotMenu;

extern void *func_ov039_020bc1dc(void);
extern void func_0204f0d4(void *scene, int handle);
extern int PXI_Init_0204f0c8(void *scene, int spriteId, int arg);
extern void Slot_SetMode2Bit(void *scene, int handle, int value);
extern void IndexedRecord_ClearActive(void *scene, int handle);
extern void IndexedRecord_SetActive(void *scene, int handle);
extern void IndexedRecords_SetFlag2(void *scene, int handle, int value);
extern void func_0204f18c(void *scene, int handle, int value);
extern void func_0204f218(void *scene, int handle, int paletteId);
extern void SlotMenu_PlaceItemSprite(SlotItem *item, void *scene, int mode, int scroll);
extern int SlotMenu_GetCursorMarkType(SlotMenu *menu);
extern void ShowMarkerElementAt(void *container, const s32 *position);

void SlotMenu_UpdateItemSprites(SlotMenu *menu, int mode, int scroll)
{
    s32 position[2];
    BOOL i;
    int slot;
    BOOL bottom;
    s8 offset;
    void *scene = func_ov039_020bc1dc();
    SlotItem *item;
    s32 top;

    if (mode || scroll % 64 == 0) {
        top = scroll;
        bottom = scroll + 0x80;
    } else {
        top = scroll - 0x20;
        bottom = 0xa0 + scroll;
    }

    for (slot = 0; slot < 8; slot += 1) {
        for (i = 0; i < 18; i++) {
            if (menu->slots[slot].items[i].handle >= 0 &&
                (!menu->slots[slot].items[i].enabled || menu->slots[slot].items[i].y < top ||
                 menu->slots[slot].items[i].y > bottom)) {
                func_0204f0d4(scene, menu->slots[slot].items[i].handle);
                menu->slots[slot].items[i].handle = -1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (menu->extras[i].handle >= 0 &&
            (!menu->extras[i].enabled || menu->extras[i].y < top || menu->extras[i].y > bottom)) {
            func_0204f0d4(scene, menu->extras[i].handle);
            menu->extras[i].handle = -1;
        }
    }

    for (slot = 0; slot < 8; slot++) {
        for (i = 0; i < 18; i++) {
            item = &menu->slots[slot].items[i];
            if (item->enabled && item->y >= top && item->y <= bottom) {
                if (item->handle < 0) {
                    item->handle = PXI_Init_0204f0c8(scene, item->spriteId, 0);
                    Slot_SetMode2Bit(scene, item->handle, 2);
                    IndexedRecord_ClearActive(scene, item->handle);
                    IndexedRecords_SetFlag2(scene, item->handle, 1);
                }
                if (item->paletteId >= 0) {
                    func_0204f218(scene, item->handle, (u16)item->paletteId);
                }
                SlotMenu_PlaceItemSprite(item, scene, mode, scroll);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        item = &menu->extras[i];
        if (item->enabled && item->y >= top && item->y <= bottom) {
            if (item->handle < 0) {
                item->handle = PXI_Init_0204f0c8(scene, item->spriteId, 0);
                if (0 == i) {
                    IndexedRecord_SetActive(scene, item->handle);
                    Slot_SetMode2Bit(scene, item->handle, 0);
                    func_0204f18c(scene, item->handle, 0);
                } else {
                    Slot_SetMode2Bit(scene, item->handle, 1);
                }
                IndexedRecords_SetFlag2(scene, item->handle, 1);
            }
            SlotMenu_PlaceItemSprite(item, scene, mode, scroll);
        }
    }

    if (2 != menu->state) {
        int selected = SlotMenu_GetCursorMarkType(menu);
        if (menu->markerHidden || 0 > selected || menu->state == 9) {
            ShowMarkerElementAt(func_ov039_020bc1dc(), NULL);
            return;
        }
        offset = 0;
        item = &menu->extras[0];
        if (0 == mode) {
            offset = 0x18;
        }
        position[0] = (item->x - 0x18 + offset) << 12;
        position[1] = (8 + item->y - scroll) << 12;
        ShowMarkerElementAt(func_ov039_020bc1dc(), position);
    }
}
