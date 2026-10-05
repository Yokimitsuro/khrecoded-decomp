#include "nitro/types.h"

extern void CreateLayerTask(void); /* CreateLayerTask */
extern void CreateEffectTask(void); /* CreateEffectTask */
extern void func_ov021_020ad174(void);
extern void DispatchCommandHandler(void); /* DispatchCommandHandler */
extern void CreatePageEffectTask(void);

void (*gEffectCreationHandlers[7])(void) = {
    NULL,
    CreateLayerTask, /* CreateLayerTask */
    CreateEffectTask, /* CreateEffectTask */
    func_ov021_020ad174,
    DispatchCommandHandler, /* DispatchCommandHandler */
    CreatePageEffectTask,
    func_ov021_020ad174,
};
