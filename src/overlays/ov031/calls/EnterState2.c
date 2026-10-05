#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern u32 func_ov001_02063404(void);
extern void ObjectManager_LoadShadowModel(void);

u32 EnterState2(void)
{
    if (func_ov001_02063404() == 1 && data_ov031_020bc820->mode != 3) {
        data_ov031_020bc820->mode = 0;
    }
    ObjectManager_LoadShadowModel();
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x8000;
    return 2;
}
