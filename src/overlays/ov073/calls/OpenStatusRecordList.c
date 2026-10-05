#include "nitro/types.h"

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
    u8 pad_174[4];
    BOOL visible;
    u8 pad_17c[0x208 - 0x17c];
    u32 recordId;
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

extern MenuSharedState *func_ov039_020bc650(void);
extern void ReleaseListView(ListView *list);
extern void ReloadStatusRecord(ListView *list, u32 id);
extern u32 MakeSharedMessageKey(u32 index);
extern void RefreshSharedUploadSlot(void);
extern int func_ov027_020b9e10(void *uploads, int layerId);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void *func_ov039_020bc1ec(void);
extern void *FindWidgetById(void *container, int id);
extern int GetPlayerLevelTier(void);
extern void InitListView(ListView *list, ListInitParams *params);
extern void UploadListPalette(ListView *list, BOOL immediate);

void OpenStatusRecordList(u32 recordId)
{
    MenuSharedState *state = func_ov039_020bc650();
    ListView *list = &state->list;
    ListInitParams params;

    list->recordId = recordId;
    if (state->page == 4) {
        if (list->opened) {
            ReleaseListView(list);
        }
        ReloadStatusRecord(list, recordId);
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
        list->opened = TRUE;
        list->visible = TRUE;
    } else {
        ReloadStatusRecord(list, recordId);
    }
}
