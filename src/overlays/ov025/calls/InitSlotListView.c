#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RowEntry {
    u16 value;
    u16 y;
    u32 unk_4;
} RowEntry;

typedef struct RowTable {
    u8 pad_00[6];
    u16 count;
    RowEntry entries[1];
} RowTable;

typedef struct SlotRecord {
    u8 pad_00[6];
    u16 parent;
    u16 index;
} SlotRecord;

typedef struct SlotTable {
    u8 pad_00[6];
    u16 count;
    SlotRecord *records[1];
} SlotTable;

typedef struct ListData {
    u16 id;
    u8 pad_02[2];
    RowTable *table;
    SlotTable *slotTable;
} ListData;

typedef struct SavedSelection {
    int id;
    u16 slotIds[3];
} SavedSelection;

typedef struct ListOverlayCell {
    int cellIndex;
    int group;
    fx32 x;
    fx32 y;
} ListOverlayCell;

typedef char *(*PathResolver)(int resourceId);

typedef struct ListView {
    void (*onChange)(void);
    ListData *data;
    BOOL asyncLoad;
    u32 field;
    u16 palette[0x30];
    SlotRecord *slots[3];
    u8 mode;
    u8 *entryStates;
    u8 *recordFlags;
    void *cellSet;
    void *highlightCell;
    void *cursorCell;
    int scrollPos;
    int scrollTarget;
    BOOL scrolling;
    int busy;
    int cursorIndex;
    int selectedIndex;
    int overlayCellCount;
    ListOverlayCell overlayCells[8];
    int normalSequence;
    int highlightSequence;
    u16 prevTouch[4];
} ListView;

typedef struct ListViewConfig {
    PathResolver resolvePath;
    void (*onChange)(void);
    ListData *data;
    BOOL asyncLoad;
    u32 field;
    u8 mode;
    void *cellSet;
    void *highlightCell;
    void *cursorCell;
    int maxSlots;
    int normalSequence;
    int highlightSequence;
} ListViewConfig;

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void MIi_CpuClear16(u16 value, void *dest, u32 size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern SavedSelection *GetSelectionPackedValueBlock(void);
extern void SetParamWord8(int value);
extern void func_ov025_020b6cc0(ListView *list, int entryIndex);
extern void func_ov025_020b6d20(ListView *list, int entryIndex);
extern void LoadPanelResource(ListView *panel, PathResolver resolvePath);

static inline int GetEntryScroll(RowEntry *entries, int index)
{
    entries += index;
    return -((entries->y - 2) * 8);
}

void InitSlotListView(ListView *list, ListViewConfig *config)
{
    SavedSelection *selection;
    SlotTable *slotTable;
    RowTable *table;
    int count;
    int index;
    int scroll;
    ListData *data;

    MI_CpuFill8(list, 0, sizeof(ListView));
    data = config->data;
    list->data = data;
    list->asyncLoad = config->asyncLoad;
    list->onChange = config->onChange;
    list->field = config->field;
    list->cellSet = config->cellSet;
    list->highlightCell = config->highlightCell;
    list->cursorCell = config->cursorCell;
    list->mode = config->mode;
    list->scrolling = FALSE;
    list->busy = 0;
    list->entryStates = NNS_FndAllocFromDefaultExpHeapEx(data->table->count, -4);
    list->recordFlags = NNS_FndAllocFromDefaultExpHeapEx(list->data->slotTable->count, -4);
    MI_CpuFill8(list->entryStates, 0, list->data->table->count);
    MI_CpuFill8(list->recordFlags, 0, list->data->slotTable->count);
    MIi_CpuClear16(0x2d6b, list->palette, sizeof(list->palette));
    selection = GetSelectionPackedValueBlock();
    if (config->data->id != selection->id) {
        SetParamWord8(-1);
    }
    slotTable = list->data->slotTable;
    table = list->data->table;
    if (selection->id >= 0) {
        for (count = 0; count < 3; count++) {
            if (selection->slotIds[count] == 0xffff) {
                break;
            }
            list->slots[count] = slotTable->records[selection->slotIds[count]];
        }
        if (count > config->maxSlots) {
            count = config->maxSlots;
        }
        if (count > 0) {
            index = list->slots[count - 1]->index;
        } else {
            index = 0;
        }
    } else {
        index = 0;
    }
    list->normalSequence = config->normalSequence;
    list->highlightSequence = config->highlightSequence;
    list->cursorIndex = index;
    list->selectedIndex = index;
    scroll = GetEntryScroll(table->entries, index);
    if (scroll > 0) {
        scroll = 0;
    } else if (scroll < -256) {
        scroll = -256;
    }
    list->scrollPos = scroll;
    list->scrollTarget = scroll;
    func_ov025_020b6cc0(list, index);
    func_ov025_020b6d20(list, index);
    LoadPanelResource(list, config->resolvePath);
}
