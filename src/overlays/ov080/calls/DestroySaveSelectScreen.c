#include "nitro/types.h"

typedef struct {
    u32 words[0x3760 / 4];
} SaveData;

typedef struct {
    u8 bytes[0x34];
} TextLayer;

typedef struct {
    u8 pad_00[4];
    s32 step : 8;
    u32 stepHigh : 24;
    u8 pad_08[0x48];
    void *tagTracker;
    void *panel;
    u8 pad_58[0x7080];
    SaveData savedGame;
    u8 pad_A838[0xc];
    TextLayer layers[4];
    void *buffer;
} SaveSelectScreen;

extern SaveData *data_0205fe0c;
extern SaveSelectScreen *data_ov080_020c5e20;
extern void func_ov027_020b833c(void *tracker);
extern void func_ov027_020b902c(void *container);
extern void ReleaseIfMarked(void *owner);
extern void FreePointerIfSet(void **ptr);
extern BOOL DestroyFndObjectList(TextLayer *layer);
extern void func_ov039_020be6c0(void);
extern void RebuildRecordCounters(void);
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern void ComputePlayerStats(SaveData *state, void *out, BOOL recompute, int scaleParam);
extern void FillSelectionRecordFromGroup(void);
extern void BuildSelectionEntryList(void);
extern void SyncSelectionRecordFromSlotEntry(void);
extern void func_0204fbb4(void);
extern void LoadSelectionPackedValues(void);

void DestroySaveSelectScreen(SaveSelectScreen *screen)
{
    func_ov027_020b833c(screen->tagTracker);
    func_ov027_020b902c(screen->panel);
    ReleaseIfMarked(screen->panel);
    FreePointerIfSet(&screen->buffer);
    DestroyFndObjectList(&screen->layers[0]);
    DestroyFndObjectList(&screen->layers[1]);
    DestroyFndObjectList(&screen->layers[3]);
    DestroyFndObjectList(&screen->layers[2]);
    *(vu16 *)0x04000050 = 0;
    func_ov039_020be6c0();
    data_ov080_020c5e20 = NULL;
    if (screen->step != 9) {
        *data_0205fe0c = screen->savedGame;
        RebuildRecordCounters();
        ComputePlayerStats(data_0205fe0c, GetOverlaySelectionRecord(0), TRUE, 0);
        FillSelectionRecordFromGroup();
        BuildSelectionEntryList();
        SyncSelectionRecordFromSlotEntry();
        func_0204fbb4();
        LoadSelectionPackedValues();
    }
}
