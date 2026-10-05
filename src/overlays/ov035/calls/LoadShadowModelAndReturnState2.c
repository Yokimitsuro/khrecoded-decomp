#include "nitro/types.h"

extern void ObjectManager_LoadShadowModel(void);

u32 LoadShadowModelAndReturnState2(void)
{
    ObjectManager_LoadShadowModel();
    return 2;
}
