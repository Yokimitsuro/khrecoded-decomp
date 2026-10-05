#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern void RebuildPanelSelection(void);
extern void ResetGroupSlotsPosition(int screenBase, int paletteBase);
extern void SetGroupSlotsVisible(int screenBase, int paletteBase, int mode);

/* Sets the panel palette base and uploads it. */
void LoadPanelPaletteBase(void) {
    RebuildPanelSelection();
    *(int *)(data_ov013_02074ce0 + 0xcc94) = 0x140000;
    ResetGroupSlotsPosition(data_ov013_02074ce0 + 0x39c, data_ov013_02074ce0 + 0xcc94);
    SetGroupSlotsVisible(data_ov013_02074ce0 + 0x39c, data_ov013_02074ce0 + 0xcc94, 1);
    *(u8 *)(data_ov013_02074ce0 + 0xd259) |= 2;
}
