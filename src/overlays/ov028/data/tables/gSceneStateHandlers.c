#include "nitro/types.h"

extern void func_ov028_020ba69c(void);
extern void func_ov028_020ba6d4(void);
extern void func_ov028_020ba720(void);
extern void func_ov028_020ba758(void);
extern void func_ov028_020ba778(void);
extern void func_ov028_020ba7fc(void);
extern void func_ov028_020ba954(void); /* SceneState_WaitPanelReady */
extern void func_ov028_020ba99c(void);
extern void func_ov028_020bab20(void);
extern void func_ov028_020bab68(void);
extern void func_ov028_020bab94(void); /* SceneState_WaitScreenIdle */
extern void EnterState12WithHalfRate(void); /* EnterState12WithHalfRate */
extern void func_ov028_020bac30(void);
extern void func_ov028_020bac5c(void);
extern void EnterOverlayTransition(void); /* EnterOverlayTransition */
extern void func_ov028_020bacd0(void);
extern void func_ov028_020bad1c(void);
extern void func_ov028_020bad50(void); /* ShutdownFieldAndSaveActorPoses */
extern void func_ov028_020bae40(void);

void (*gSceneStateHandlers[19])(void) = {
    func_ov028_020ba69c,
    func_ov028_020ba6d4,
    func_ov028_020ba720,
    func_ov028_020ba758,
    func_ov028_020ba778,
    func_ov028_020ba7fc,
    func_ov028_020ba954, /* SceneState_WaitPanelReady */
    func_ov028_020ba99c,
    func_ov028_020bab20,
    func_ov028_020bab68,
    func_ov028_020bab94, /* SceneState_WaitScreenIdle */
    EnterState12WithHalfRate, /* EnterState12WithHalfRate */
    func_ov028_020bac30,
    func_ov028_020bac5c,
    EnterOverlayTransition, /* EnterOverlayTransition */
    func_ov028_020bacd0,
    func_ov028_020bad1c,
    func_ov028_020bad50, /* ShutdownFieldAndSaveActorPoses */
    func_ov028_020bae40,
};
