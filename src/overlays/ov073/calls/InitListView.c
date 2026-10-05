#include "nitro/types.h"

typedef struct ListEntry {
    u16 unk_0;
    u16 column;
    u16 row;
    u16 unk_6;
} ListEntry;

typedef struct ListTable {
    u8 pad_00[6];
    u16 count;
    ListEntry entries[1];
} ListTable;

typedef struct SlotRecord {
    u8 pad_00[6];
    u16 entryIndex;
    u16 nextEntryIndex;
} SlotRecord;

typedef struct SlotLinkTable {
    u8 pad_00[6];
    u16 count;
    SlotRecord *records[1];
} SlotLinkTable;

typedef struct ListData {
    u16 id;
    u8 pad_02[2];
    ListTable *table;
    SlotLinkTable *links;
} ListData;

typedef struct SelectionState {
    int value;
    u16 ids[3];
} SelectionState;

typedef struct ListInitParams {
    u32 (*makeMessageKey)(u32 index);
    void (*refresh)(void);
    ListData *data;
    int unk_0c;
    int uploadSlot;
    u8 selectionFlag;
    void *cellSet;
    void *frameWidget;
    void *cursorWidget;
    int maxDepth;
    int normalSequence;
    int highlightSequence;
} ListInitParams;

typedef struct ListView {
    void (*onChange)(void);
    ListData *data;
    int unk_08;
    int uploadSlot;
    u16 palette[0x30];
    SlotRecord *slots[3];
    u8 selectionFlag;
    u8 pad_7d[3];
    u8 *entryUsage;
    u8 *recordStates;
    void *cellSet;
    void *frameWidget;
    void *cursorWidget;
    int scrollX;
    int targetX;
    BOOL scrolling;
    BOOL cancelled;
    int cursorIndex;
    int selectedIndex;
    u8 pad_ac[0x130 - 0xac];
    int normalSequence;
    int highlightSequence;
    u8 pad_138[0x140 - 0x138];
} ListView;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MIi_CpuClear16(u16 value, void *dest, u32 size);
extern SelectionState *GetSelectionPackedValueBlock(void);
extern void SetParamWord8(int value);
extern void SelectListEntry(ListView *list, int entryIndex);
extern void PlaceCursorAtListEntry(ListView *list, int entryIndex);
extern void LoadListLayoutFile(ListView *list, u32 (*makeMessageKey)(u32 index));

void InitListView(ListView *list, ListInitParams *params)
{
    ListData *data;
    SelectionState *selection;
    ListTable *table;
    SlotLinkTable *links;
    int depth;
    int cursor;
    u16 id;
    int scroll;
    ListEntry *entry;

    MI_CpuFill8(list, 0, sizeof(ListView));
    data = params->data;
    list->data = data;
    list->unk_08 = params->unk_0c;
    list->onChange = params->refresh;
    list->uploadSlot = params->uploadSlot;
    list->cellSet = params->cellSet;
    list->frameWidget = params->frameWidget;
    list->cursorWidget = params->cursorWidget;
    list->selectionFlag = params->selectionFlag;
    list->scrolling = FALSE;
    list->cancelled = FALSE;
    list->entryUsage = NNS_FndAllocFromDefaultExpHeapEx(data->table->count, -4);
    list->recordStates = NNS_FndAllocFromDefaultExpHeapEx(list->data->links->count, -4);
    MI_CpuFill8(list->entryUsage, 0, list->data->table->count);
    MI_CpuFill8(list->recordStates, 0, list->data->links->count);
    MIi_CpuClear16(0x2d6b, list->palette, sizeof(list->palette));
    selection = GetSelectionPackedValueBlock();
    if (params->data->id != selection->value) {
        SetParamWord8(-1);
    }
    links = list->data->links;
    table = list->data->table;
    if (selection->value >= 0) {
        for (depth = 0; depth < 3; depth++) {
            id = selection->ids[depth];
            if (id == 0xffff) {
                break;
            }
            list->slots[depth] = links->records[id];
        }
        if (depth > params->maxDepth) {
            depth = params->maxDepth;
        }
        if (depth > 0) {
            cursor = list->slots[depth - 1]->nextEntryIndex;
        } else {
            cursor = 0;
        }
    } else {
        cursor = 0;
    }
    list->normalSequence = params->normalSequence;
    list->highlightSequence = params->highlightSequence;
    list->cursorIndex = cursor;
    list->selectedIndex = cursor;
    entry = table->entries;
    entry += cursor;
    scroll = -((entry->column - 2) * 8);
    if (scroll > 0) {
        scroll = 0;
    } else if (scroll < -0x100) {
        scroll = -0x100;
    }
    list->scrollX = scroll;
    list->targetX = scroll;
    SelectListEntry(list, cursor);
    PlaceCursorAtListEntry(list, cursor);
    LoadListLayoutFile(list, params->makeMessageKey);
}
