#include "nitro/types.h"

extern void func_ov021_020acde0(void); /* CreateLayerTask */
extern void func_ov021_020acefc(void); /* CreateEffectTask */
extern void func_ov021_020ad174(void);
extern void func_ov021_020ad528(void); /* DispatchCommandHandler */
extern void func_ov055_020d3dfc(void);

void (*gEffectCreationHandlers[7])(void) = {
    NULL,
    func_ov021_020acde0, /* CreateLayerTask */
    func_ov021_020acefc, /* CreateEffectTask */
    func_ov021_020ad174,
    func_ov021_020ad528, /* DispatchCommandHandler */
    func_ov055_020d3dfc,
    func_ov021_020ad174,
};
