#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x138];
    int defaultPage;
    u8 pad_13c[0x148 - 0x13c];
    int selectedRow;
    u8 pad_14c[0x1dc - 0x14c];
    void *listEntry;
} Ov086Menu;

extern Ov086Menu *data_ov086_020c3020;
extern void SetSecondaryElementEnabled(BOOL enabled);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern BOOL AcquireRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern void SetupRecordSubScreenLayers(void);
extern void InitRecordTileTable(Ov086Menu *menu);
extern void LoadRecordSubScreenGraphics(Ov086Menu *menu);
extern void InitRecordPanelDigits(Ov086Menu *menu);
extern void InitRecordPanelText(Ov086Menu *menu);
extern void func_ov086_020c082c(Ov086Menu *menu);
extern void *AllocateListEntry(void *callback);
extern BOOL UpdateRecordScrollOffset(void);

BOOL InitRecordMenu(Ov086Menu *menu)
{
    SetSecondaryElementEnabled(FALSE);
    menu->defaultPage = ReadGlobalPackedBits(0x330b, 10) / 100 - 1;
    AcquireRecordManager();
    AcquireRecordSlot(0, 0);
    data_ov086_020c3020 = menu;
    menu->selectedRow = -1;
    SetupRecordSubScreenLayers();
    InitRecordTileTable(menu);
    LoadRecordSubScreenGraphics(menu);
    InitRecordPanelDigits(menu);
    InitRecordPanelText(menu);
    func_ov086_020c082c(menu);
    menu->listEntry = AllocateListEntry(UpdateRecordScrollOffset);
    return TRUE;
}
