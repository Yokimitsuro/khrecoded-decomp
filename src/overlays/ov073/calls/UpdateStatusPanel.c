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
    int normalSequence;
    int highlightSequence;
} ListInitParams;

typedef struct StatusPanel {
    u8 pad_000[0x144];
    Record *record;
    u8 uploads[0x168 - 0x148];
    BOOL needsRedraw;
    BOOL uploadsReady;
    BOOL opened;
    u8 pad_174[0x184 - 0x174];
    void *screenBuffer;
    void *charBuffer;
    u8 pad_18c[0x1cc - 0x18c];
    u8 textLayer[0x200 - 0x1cc];
    int selectedRecord;
    int pendingFrames;
} StatusPanel;

typedef struct RecordEntry {
    u8 pad_00[0x2c];
    const u16 *name;
} RecordEntry;

typedef struct StatusMenu {
    s8 page;
    u8 pad_01[2];
    u8 flags;
    u8 pad_04[0x11cc - 0x04];
    u8 strings[1];
} StatusMenu;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x1e];
    u8 flag;
} OverlaySelectionRecord;

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern u32 MakeSharedMessageKey(u32 index);
extern void RefreshSharedUploadSlot(void);
extern int func_ov027_020b9e10(void *uploads, int layerId);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void *func_ov039_020bc1ec(void);
extern void *FindWidgetById(void *container, int id);
extern int GetPlayerLevelTier(void);
extern void InitListView(StatusPanel *list, ListInitParams *params);
extern void UploadListPalette(StatusPanel *list, BOOL immediate);
extern BOOL func_ov039_020bc0f4(void);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);
extern int func_ov073_020c3fc4(StatusPanel *panel);
extern void CallVirtualHandlerSlot1(void *context, int arg);
extern u16 *func_ov027_020ba2c8(void *table, int index);
extern void *func_ov039_020bc9cc(void);
extern RecordEntry *GetRecordSlotPair1Entry(int index);
extern void func_02001704(void *layer, int x, int y, int color, u32 flags, const u16 *text, void *fallbackFont, int maxWidth);
extern void FlushBufferAndRunCallback(void *context);

BOOL UpdateStatusPanel(StatusMenu *menu, StatusPanel *panel)
{
    ListInitParams params;
    void *container;
    int recordIndex;

    if (panel->pendingFrames == 1) {
        panel->pendingFrames = 0;
    }
    if (panel->needsRedraw) {
        NNSi_FndFreeFromDefaultHeap(panel->screenBuffer);
        NNSi_FndFreeFromDefaultHeap(panel->charBuffer);
        panel->charBuffer = NULL;
        panel->screenBuffer = NULL;
        if (!panel->opened) {
            params.makeMessageKey = MakeSharedMessageKey;
            params.refresh = RefreshSharedUploadSlot;
            params.record = panel->record;
            params.unk_0c = 0;
            params.uploadSlot = func_ov027_020b9e10(panel->uploads, 0x1a);
            params.selectionFlag = GetOverlaySelectionRecord(0)->flag;
            params.container = func_ov039_020bc1ec();
            params.frameWidget = FindWidgetById(func_ov039_020bc1ec(), 0xe);
            params.cursorWidget = FindWidgetById(func_ov039_020bc1ec(), 0x3b);
            params.levelTier = GetPlayerLevelTier();
            params.normalSequence = 0x1a;
            params.highlightSequence = 0x1b;
            InitListView(panel, &params);
            UploadListPalette(panel, TRUE);
            container = func_ov039_020bc1ec();
            SetEntrySlotsVisible(container, params.frameWidget, func_ov039_020bc0f4() == FALSE);
            panel->opened = TRUE;
        }
        panel->uploadsReady = FALSE;
        panel->needsRedraw = FALSE;
        panel->pendingFrames--;
    }
    if ((menu->flags & 2) && (recordIndex = func_ov073_020c3fc4(panel)) != panel->selectedRecord) {
        CallVirtualHandlerSlot1(panel->textLayer, 0);
        if (recordIndex == -1) {
            func_02001704(panel->textLayer, 4, 0, 2, 10, func_ov027_020ba2c8(menu->strings, 0x24),
                          func_ov039_020bc9cc(), 0xe4);
        } else {
            func_02001704(panel->textLayer, 4, 0, 2, 10, GetRecordSlotPair1Entry(recordIndex)->name,
                          func_ov039_020bc9cc(), 0xe4);
        }
        FlushBufferAndRunCallback(panel->textLayer);
        panel->selectedRecord = recordIndex;
    }
    if (panel->pendingFrames != 0) {
        return TRUE;
    }
    return FALSE;
}
