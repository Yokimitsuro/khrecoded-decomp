#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern void func_ov013_020712e8(void);
extern void func_ov002_020680a4(int screenBase, int paletteBase);
extern void func_ov002_02068248(int screenBase, int paletteBase, int mode);

/* Sets the panel palette base and uploads it. */
void LoadPanelPaletteBase(void) {
    func_ov013_020712e8();
    *(int *)(data_ov013_02074ce0 + 0xcc94) = 0x140000;
    func_ov002_020680a4(data_ov013_02074ce0 + 0x39c, data_ov013_02074ce0 + 0xcc94);
    func_ov002_02068248(data_ov013_02074ce0 + 0x39c, data_ov013_02074ce0 + 0xcc94, 1);
    *(u8 *)(data_ov013_02074ce0 + 0xd259) |= 2;
}
