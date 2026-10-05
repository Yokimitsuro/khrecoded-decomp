#include "nitro/types.h"

extern void UpdateHudNoticeMessage(void); /* UpdateHudNoticeMessage */
extern void UpdateMenuSlideIn(void);
extern void func_ov001_020708f0(void); /* _fp_init */
extern void UpdateSceneSlideOut(void); /* UpdateSceneSlideOut */
extern void G2_GetBG1ScrPtr(void);
extern void G2_GetBG2ScrPtr(void);
extern void G2_GetBG3ScrPtr(void);

void (*gHudNoticeStateHandlers[4])(void) = {
    UpdateHudNoticeMessage, /* UpdateHudNoticeMessage */
    UpdateMenuSlideIn,
    func_ov001_020708f0, /* _fp_init */
    UpdateSceneSlideOut, /* UpdateSceneSlideOut */
};

void (*gMainBgScreenGetters[3])(void) = {
    G2_GetBG1ScrPtr,
    G2_GetBG2ScrPtr,
    G2_GetBG3ScrPtr,
};
