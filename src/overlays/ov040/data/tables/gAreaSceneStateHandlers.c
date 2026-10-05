#include "nitro/types.h"

extern void func_ov040_020bcc80(void); /* ResetAreaMeshValues */
extern void func_ov040_020bcd28(void);
extern void func_ov040_020bcd6c(void); /* FinishAreaSceneLoad */
extern void func_ov040_020bce70(void);
extern void func_ov040_020bd0f4(void);
extern void func_ov040_020bd128(void); /* UpdateAreaSceneState */
extern void func_ov040_020bd2b8(void);
extern void func_ov040_020bd384(void); /* TickIntroRotation */
extern void func_ov040_020bd418(void);
extern void func_ov040_020bd484(void); /* FadeInAreaScreens */
extern void func_ov040_020bd548(void);
extern void func_ov040_020bd568(void);
extern void func_ov040_020bd5c4(void); /* EnterState13WithHalfRate */
extern void func_ov040_020bd5e0(void);
extern void func_ov040_020bd604(void);
extern void func_ov040_020bd624(void);
extern void func_ov040_020bd648(void);
extern void func_ov040_020bd68c(void); /* FinishAreaTransition */
extern void func_ov040_020bd748(void); /* Gfd_DefaultFreeTexVram */

void (*gAreaSceneStateHandlers[19])(void) = {
    func_ov040_020bcc80, /* ResetAreaMeshValues */
    func_ov040_020bcd28,
    func_ov040_020bcd6c, /* FinishAreaSceneLoad */
    func_ov040_020bce70,
    func_ov040_020bd0f4,
    func_ov040_020bd128, /* UpdateAreaSceneState */
    func_ov040_020bd2b8,
    func_ov040_020bd384, /* TickIntroRotation */
    func_ov040_020bd418,
    func_ov040_020bd484, /* FadeInAreaScreens */
    func_ov040_020bd548,
    func_ov040_020bd568,
    func_ov040_020bd5c4, /* EnterState13WithHalfRate */
    func_ov040_020bd5e0,
    func_ov040_020bd604,
    func_ov040_020bd624,
    func_ov040_020bd648,
    func_ov040_020bd68c, /* FinishAreaTransition */
    func_ov040_020bd748, /* Gfd_DefaultFreeTexVram */
};
