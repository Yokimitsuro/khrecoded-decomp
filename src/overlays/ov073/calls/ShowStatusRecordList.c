#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

typedef struct Record Record;

typedef struct ListInitParams {
    u32 (*makeMessageKey)(u32 index);
    void (*refresh)(void);
    Record *record;
    int unk_0c;
    int uploadSlot;
    u8 selectionFlag;
    void *container;
    void *frameWidget;
    void *cursorWidget;
    int levelTier;
    int layerId;
    int cursorLayerId;
} ListInitParams;

typedef struct ListView {
    u8 pad_000[0x144];
    Record *record;
    u8 uploads[0x170 - 0x148];
    BOOL opened;
    BOOL restoreLayers;
} ListView;

typedef struct MenuSharedState {
    s8 page;
    u8 pad_001[0xb44 - 1];
    ListView list;
} MenuSharedState;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x1e];
    u8 flag;
} OverlaySelectionRecord;

typedef struct SelectionState {
    u8 pad_00[4];
    u8 values[6];
} SelectionState;

extern MenuSharedState *func_ov039_020bc650(void);
extern SelectionState *GetSelectionPackedValueBlock(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void OS_WaitVBlankIntr(void);
extern u32 MakeSharedMessageKey(u32 index);
extern void RefreshSharedUploadSlot(void);
extern int func_ov027_020b9e10(void *uploads, int layerId);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void *func_ov039_020bc1ec(void);
extern void *FindWidgetById(void *container, int id);
extern int GetPlayerLevelTier(void);
extern void InitListView(ListView *list, ListInitParams *params);
extern void UploadListPalette(ListView *list, BOOL immediate);
extern BOOL func_ov039_020bc0f4(void);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);
extern void GetListWidgetEntryIds(ListView *list, u8 *values);

void ShowStatusRecordList(u8 *values)
{
    MenuSharedState *state = func_ov039_020bc650();
    ListView *list = &state->list;
    ListInitParams params;
    u32 layers;
    void *container;

    if (state->page != 4) {
        MI_CpuCopy8(GetSelectionPackedValueBlock()->values, values, 6);
        return;
    }
    if (!list->opened) {
        layers = (REG_DB_DISPCNT & 0x1f00) >> 8;
        OS_WaitVBlankIntr();
        REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1000;
        params.makeMessageKey = MakeSharedMessageKey;
        params.refresh = RefreshSharedUploadSlot;
        params.record = list->record;
        params.unk_0c = 0;
        params.uploadSlot = func_ov027_020b9e10(list->uploads, 0x1a);
        params.selectionFlag = GetOverlaySelectionRecord(0)->flag;
        params.container = func_ov039_020bc1ec();
        params.frameWidget = FindWidgetById(func_ov039_020bc1ec(), 0xe);
        params.cursorWidget = FindWidgetById(func_ov039_020bc1ec(), 0x3b);
        params.levelTier = GetPlayerLevelTier();
        params.layerId = 0x1a;
        params.cursorLayerId = 0x1b;
        InitListView(list, &params);
        UploadListPalette(list, TRUE);
        container = func_ov039_020bc1ec();
        SetEntrySlotsVisible(container, params.frameWidget, func_ov039_020bc0f4() == FALSE);
        list->opened = TRUE;
        if (list->restoreLayers) {
            OS_WaitVBlankIntr();
            REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (layers << 8);
        }
    }
    GetListWidgetEntryIds(list, values);
}
