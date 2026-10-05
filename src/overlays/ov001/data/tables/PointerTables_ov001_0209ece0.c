#include "nitro/types.h"

extern void func_ov001_020705a4(void); /* UpdateHudNoticeMessage */
extern void func_ov001_02070870(void);
extern void func_ov001_020708f0(void); /* _fp_init */
extern void UpdateSceneSlideOut(void); /* UpdateSceneSlideOut */
extern void G2_GetBG1ScrPtr(void);
extern void G2_GetBG2ScrPtr(void);
extern void G2_GetBG3ScrPtr(void);

void (*gHudNoticeStateHandlers[4])(void) = {
    func_ov001_020705a4, /* UpdateHudNoticeMessage */
    func_ov001_02070870,
    func_ov001_020708f0, /* _fp_init */
    UpdateSceneSlideOut, /* UpdateSceneSlideOut */
};

void (*gMainBgScreenGetters[3])(void) = {
    G2_GetBG1ScrPtr,
    G2_GetBG2ScrPtr,
    G2_GetBG3ScrPtr,
};
