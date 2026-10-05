#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern void func_ov013_0206fbbc(void);
extern void RefreshProgressCaption(void);
extern void func_ov013_020716e4(int mode);

/* Selects panel tint variant 5. */
void SelectPanelTint5(void) {
    *(u8 *)(data_ov013_02074ce0 + 0x2ee) = 5;
    *(s8 *)(data_ov013_02074ce0 + 0x2f0) =
        *(s8 *)(data_ov013_02074ce0 + 0x2ee) + *(s8 *)(data_ov013_02074ce0 + 0x2ef);
    *(int *)(data_ov013_02074ce0 + 0x2fc) =
        (int)*(s8 *)(data_ov013_02074ce0 + 0x2ee) * *(int *)(data_ov013_02074ce0 + 0x300);
    func_ov013_0206fbbc();
    if (*(int *)(data_ov013_02074ce0 + 0x2e4) != (int)*(s8 *)(data_ov013_02074ce0 + 0x2f0)) {
        RefreshProgressCaption();
        return;
    }
    func_ov013_020716e4(2);
}
