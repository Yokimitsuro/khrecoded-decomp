#include "nitro/types.h"

extern void OpenDefaultRectDialog(void);
extern void OpenPreviewDialog(void);
extern void func_ov075_020cc5c8(void);
extern void UpdateFlagToggleGrid(void);
extern void UpdateVolumeSlider(void);

void (*const gOv075StateHandlers[5])(void) = {
    OpenDefaultRectDialog,
    OpenPreviewDialog,
    func_ov075_020cc5c8,
    UpdateFlagToggleGrid,
    UpdateVolumeSlider,
};
