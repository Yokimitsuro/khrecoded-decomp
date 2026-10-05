#include "nitro/types.h"

typedef struct {
    u16 unk_00;
    s16 slot;
    u32 unk_04;
    u32 unk_08;
} MenuSlotDef;

typedef struct {
    MenuSlotDef defs[16];
    u32 values[16];
    s32 count;
} MenuSlotTable;

typedef struct {
    u8 pad_000[0x2c];
    MenuSlotTable slots;
} SelectionRecord;

typedef struct {
    u32 value;
} FieldMenuEntry;

typedef struct {
    u8 objects[0x34];
    u8 cells[0xac - 0x34];
    void *entries;
    void *shortcuts;
    void *layout;
    u8 pad_0b8[0xe0 - 0xb8];
    void *bufferA;
    void *bufferB;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern FieldMenu *NNSi_FndGetCurrentRootHeap(void);
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern FieldMenuEntry *FindFieldMenuEntryById(FieldMenu *menu, int list, s32 id, int *outIndex);
extern void DestroyFndObjectList(void *list);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void DestroyFieldMenu(void) {
    FieldMenu *menu = NNSi_FndGetCurrentRootHeap();
    MenuSlotTable *slots;
    int i = 0;

    slots = &GetOverlaySelectionRecord(0)->slots;

    for (; i < slots->count; i++) {
        FieldMenuEntry *entry = FindFieldMenuEntryById(menu, 0, i, NULL);
        if (entry != NULL) {
            slots->values[slots->defs[i].slot] = entry->value;
        }
    }
    DestroyFndObjectList(menu->objects);
    DestroyFndObjectList(menu->cells);
    if (menu->entries != NULL) {
        NNSi_FndFreeFromDefaultHeap(menu->entries);
    }
    if (menu->bufferA != NULL) {
        NNSi_FndFreeFromDefaultHeap(menu->bufferA);
    }
    if (menu->bufferB != NULL) {
        NNSi_FndFreeFromDefaultHeap(menu->bufferB);
    }
    if (menu->layout != NULL) {
        NNSi_FndFreeFromDefaultHeap(menu->layout);
    }
    if (menu->shortcuts != NULL) {
        NNSi_FndFreeFromDefaultHeap(menu->shortcuts);
    }
    data_ov001_020a04d0.menu = NULL;
}
